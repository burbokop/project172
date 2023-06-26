#include "units.h"

#include "projectile.h"
#include "ship.h"
#include "station.h"
#include "unit.h"
#include <src/assettools/assetprovider.h>
#include <src/gameapplication.h>

void proj172::core::registerUnits(e172::GameApplication &app)
{
    app.assetProvider()->registerType<Unit>();
    app.assetProvider()->registerType<Ship>();
    app.assetProvider()->registerType<Station>();
    app.assetProvider()->registerType<Projectile>();
}
