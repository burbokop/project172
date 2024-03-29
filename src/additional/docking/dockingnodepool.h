#pragma once

#include <e172/math/vector.h>
#include <list>

namespace e172 {
class PhysicalObject;
class AbstractRenderer;
}

class DockingNodePool {
public:
    struct Node {
        static inline size_t nextNodeId = 0;
        e172::Vector<double> m_offset;
        double m_angle;
        bool m_locked = false;
        bool m_isValid = false;
        size_t m_nodeId = nextNodeId++;
    public:
        e172::Vector<double> offset() const;
        e172::Vector<double> globalPosition(const e172::PhysicalObject *object) const;

        double angle() const;
        bool isValid() const;
        size_t nodeId() const;

        friend std::ostream &operator<< (std::ostream& stream, const Node& node);
    };
private:
    std::list<Node> m_nodes;
public:
    DockingNodePool();
    void clearNodes();
    void addNode(const e172::Vector<double> &offset, double angle);

    Node nextFreeNode();
    bool returnToPool(const Node& node);

};

