#include "dockingnodepool.h"

#include <e172/graphics/abstractrenderer.h>
#include <e172/math/physicalobject.h>

DockingNodePool::DockingNodePool() {

}

void DockingNodePool::clearNodes() {
    m_nodes.clear();
}

void DockingNodePool::addNode(const e172::Vector<double> &offset, double angle) {
    Node n;
    n.m_offset = offset;
    n.m_angle = angle;
    n.m_isValid = true;
    m_nodes.push_back(n);
}

DockingNodePool::Node DockingNodePool::nextFreeNode() {
    for(auto& n : m_nodes) {
        if(!n.m_locked) {
            n.m_locked = true;
            return n;
        }
    }
    return Node();
}

bool DockingNodePool::returnToPool(const DockingNodePool::Node &node) {
    for(auto& n : m_nodes) {
        if(n.m_nodeId == node.m_nodeId) {
            n.m_locked = false;
            return true;
        }
    }
    return false;
}


size_t DockingNodePool::Node::nodeId() const {
    return m_nodeId;
}

std::ostream &operator<<(std::ostream &stream, const DockingNodePool::Node &node) {
    return stream << "{ offset: " << node.m_offset << ", angle: " << node.m_angle << " }";
}

e172::Vector<double> DockingNodePool::Node::offset() const {
    return m_offset;
}

e172::Vector<double> DockingNodePool::Node::globalPosition(const e172::PhysicalObject *object) const
{
    if (object) {
        return object->position() + object->rotationMatrix() * offset();
    } else {
        return {};
    }
}

double DockingNodePool::Node::angle() const {
    return m_angle;
}

bool DockingNodePool::Node::isValid() const {
    return m_isValid;
}
