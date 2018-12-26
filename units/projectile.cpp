#include "projectile.h"

Projectile::Projectile() {
    setIdleEnabled(false);
}

Projectile::Projectile(Loadable *tmp) : Movable (tmp) {
    setIdleEnabled(false);
}

void Projectile::loop(std::vector<Worker *> *others, Event *event) {

}
