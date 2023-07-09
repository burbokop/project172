#include "capabilitysynchronizer.h"

#include "../packagetype.h"
#include "../units/unit.h"
#include <e172/gameapplication.h>
#include <e172/net/gameclient.h>
#include <e172/net/gameserver.h>

void proj172::core::CapabilitySyncClient::entityAdded(const e172::ptr<e172::Entity> &entity)
{
    assert(m_client);
    m_client->unknownPackageReceived().connect(this, [this](e172::ReadPackage package) { todo(); });
}

void proj172::core::CapabilitySyncClient::entityRemoved(const e172::Entity::Id &id) {}

proj172::core::CapabilitySyncServer::CapabilitySyncServer(std::shared_ptr<e172::GameServer> server)
    : m_server(std::move(server))
{
    assert(m_server);
    m_server->clientConnected().connect(this, [this](e172::PackedClientId clientId) {
        for (const auto &e : m_server->app().entities()) {
            if (const auto &unit = e172::smart_cast<Unit>(e)) {
                for (const auto &cap : unit->capabilities()) {
                    m_server->sendCustomPackage(clientId,
                                                ~PackageType::AddCapability,
                                                [unit, cap](e172::WritePackage p) {
                                                    p.write(e172::PackedEntityId(unit->entityId()));
                                                    p.writeDyn(cap->meta().typeName());
                                                    p.write(e172::PackedEntityId(cap->entityId()));
                                                });
                }
            }
        }
    });
}

void proj172::core::CapabilitySyncServer::entityAdded(const e172::ptr<e172::Entity> &entity)
{
    auto unit = e172::smart_cast<Unit>(entity);
    unit->capabilityAdded().connect(this, [this](const e172::ptr<Capability> &cap) {
        m_server->broadcastCustomPackage(~PackageType::AddCapability,
                                         [](e172::WritePackage package) { todo(); });
    });
    unit->capabilityRemoved().connect(this, [this](const e172::Entity::Id &cap) {
        m_server->broadcastCustomPackage(~PackageType::RemoveCapability,
                                         [](e172::WritePackage package) { todo(); });
    });
}

void proj172::core::CapabilitySyncServer::entityRemoved(const e172::Entity::Id &) {}
