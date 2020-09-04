#ifndef WIREVERTEXOBJECT_H
#define WIREVERTEXOBJECT_H

#include "abstractvertexobject.h"

#include "../vertex.h"

namespace e172vp {

class WireVertexObject : public AbstractVertexObject {
    vk::Buffer m_vertexBuffer;
    vk::DeviceMemory m_vertexBufferMemory;
    vk::Buffer m_indexBuffer;
    vk::DeviceMemory m_indexBufferMemory;

    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
public:
    WireVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
    ~WireVertexObject();

    void setVertices(const std::vector<e172vp::Vertex> &vertices);

    // AbstractVertexObject interface
public:
    virtual vk::Buffer vertexBuffer() const override;
    virtual vk::Buffer indexBuffer() const override;
    virtual uint32_t indexCount() const override;
    virtual void update(int) override;
    virtual std::vector<vk::DescriptorSet> descriptorSets() override;
    virtual void initialize(const GraphicsObject *graphicsObject, int, const DescriptorSetLayout *, const DescriptorSetLayout *) override;
};
}
#endif // WIREVERTEXOBJECT_H
