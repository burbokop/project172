#pragma once

#include <src/entitylifetimeobserver.h>

namespace e172 {
class GameServer;
class GameClient;
} // namespace e172

namespace proj172::core {

class CapabilitySyncClient : public e172::Object, public e172::EntityLifeTimeObserver
{
public:
    CapabilitySyncClient(std::shared_ptr<e172::GameClient> client)
        : m_client(std::move(client)){};

    // EntityLifeTimeObserver interface
protected:
    void entityAdded(const e172::ptr<e172::Entity> &) override;
    void entityRemoved(const e172::Entity::Id &) override;

private:
    std::shared_ptr<e172::GameClient> m_client;
};

class CapabilitySyncServer : public e172::Object, public e172::EntityLifeTimeObserver
{
public:
    CapabilitySyncServer(std::shared_ptr<e172::GameServer> server);
    ;

    // EntityLifeTimeObserver interface
protected:
    void entityAdded(const e172::ptr<e172::Entity> &) override;
    void entityRemoved(const e172::Entity::Id &) override;

private:
    std::shared_ptr<e172::GameServer> m_server;
};

} // namespace proj172::core
