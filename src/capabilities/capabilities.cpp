#include "capabilities.h"

#include "docker.h"
#include "factory.h"
#include "modules/engine.h"
#include "modules/thruster.h"
#include "modules/warpdrive.h"
#include "modules/weapon.h"
#include "player.h"
#include <e172/assettools/assetprovider.h>
#include <e172/gameapplication.h>

void proj172::core::registerCapabilities(e172::GameApplication &app)
{
    app.assetProvider()->registerType<Player>();
    app.assetProvider()->registerType<Engine>();
    app.assetProvider()->registerType<Weapon>();
    app.assetProvider()->registerType<WarpDrive>();
    app.assetProvider()->registerType<Thruster>();
    app.assetProvider()->registerType<Factory>();
    app.assetProvider()->registerType<Docker>();
}
