#include "units.h"

#include "projectile.h"
#include "ship.h"
#include "station.h"
#include "unit.h"
#include <e172/assettools/assetprovider.h>
#include <e172/gameapplication.h>

void proj172::core::registerUnits(e172::GameApplication &app)
{
    app.assetProvider()->registerType<Unit>();
    app.assetProvider()->registerType<Ship>();
    app.assetProvider()->registerType<Station>();
    app.assetProvider()->registerType<Projectile>();
}
