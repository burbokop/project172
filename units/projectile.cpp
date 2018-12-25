#include "projectile.h"

Projectile::Projectile() {
}

Projectile::Projectile(Loadable *tmp) : Movable (tmp) {
}

void Projectile::loop(std::vector<Worker *> *others, Event *event) {

}
