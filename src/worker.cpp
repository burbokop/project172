#include "worker.h"

#include "objectregistry.h"

Worker::Worker() {
    ObjectRegistry::getInstance()->registerObject(this);
}

Worker::~Worker() {
    ObjectRegistry::getInstance()->markAsDeleted(this);
}
