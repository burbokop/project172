#include "dockingnodepool.h"

DockingNodePool::DockingNodePool() {

}

void DockingNodePool::clearNodes() {
    m_nodes.clear();
}

void DockingNodePool::addNode(const e172::Vector &offset, double angle) {
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

e172::Vector DockingNodePool::Node::offset() const {
    return m_offset;
}

double DockingNodePool::Node::angle() const {
    return m_angle;
}

bool DockingNodePool::Node::isValid() const {
    return m_isValid;
}
