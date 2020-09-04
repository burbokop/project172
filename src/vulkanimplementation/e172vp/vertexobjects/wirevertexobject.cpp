#include "wirevertexobject.h"

#include "../tools/buffer.h"

#include "../graphicsobject/graphicsobject.h"

e172vp::WireVertexObject::WireVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) {
    m_vertices = vertices;
    m_indices = indices;
}

e172vp::WireVertexObject::~WireVertexObject() {
    if(m_vertexBuffer)
        graphicsObject()->logicalDevice().destroyBuffer(m_vertexBuffer);
    if(m_vertexBufferMemory)
        graphicsObject()->logicalDevice().freeMemory(m_vertexBufferMemory);
    if(m_indexBuffer)
        graphicsObject()->logicalDevice().destroyBuffer(m_indexBuffer);
    if(m_indexBufferMemory)
        graphicsObject()->logicalDevice().freeMemory(m_indexBufferMemory);
}

void e172vp::WireVertexObject::initialize(const e172vp::GraphicsObject *graphicsObject, int, const e172vp::DescriptorSetLayout *, const e172vp::DescriptorSetLayout *) {
    Buffer::createVertexBuffer(graphicsObject, m_vertices, &m_vertexBuffer, &m_vertexBufferMemory);
    Buffer::createIndexBuffer(graphicsObject, m_indices, &m_indexBuffer, &m_indexBufferMemory);
}


void e172vp::WireVertexObject::setVertices(const std::vector<e172vp::Vertex> &vertices) {
    if(m_vertices != vertices) {
        m_vertices = vertices;
        Buffer::updateVertexBuffer(graphicsObject(), vertices, m_vertexBuffer);
    }
}

vk::Buffer e172vp::WireVertexObject::vertexBuffer() const {
    return m_vertexBuffer;
}

vk::Buffer e172vp::WireVertexObject::indexBuffer() const {
    return m_indexBuffer;
}

uint32_t e172vp::WireVertexObject::indexCount() const {
    return m_indices.size();
}

void e172vp::WireVertexObject::update(int) {}

std::vector<vk::DescriptorSet> e172vp::WireVertexObject::descriptorSets() {
    return std::vector<vk::DescriptorSet>();
}


