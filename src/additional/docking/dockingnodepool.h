#ifndef DOCKINGNODEPOOL_H
#define DOCKINGNODEPOOL_H

#include <src/math/vector.h>
#include <list>

namespace e172 {
class AbstractRenderer;
}

class DockingNodePool {
public:
    struct Node {
        static inline size_t nextNodeId = 0;
        e172::Vector m_offset;
        double m_angle;
        bool m_locked = false;
        bool m_isValid = false;
        size_t m_nodeId = nextNodeId++;
    public:
        e172::Vector offset() const;
        double angle() const;
        bool isValid() const;
        size_t nodeId() const;
    };
private:
    std::list<Node> m_nodes;
public:
    DockingNodePool();
    void clearNodes();
    void addNode(const e172::Vector &offset, double angle);

    Node nextFreeNode();
    bool returnToPool(const Node& node);

};

#endif // DOCKINGNODEPULL_H
