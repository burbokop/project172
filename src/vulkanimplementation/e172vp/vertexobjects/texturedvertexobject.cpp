#include "texturedvertexobject.h"

e172vp::TexturedVertexObject::TexturedVertexObject() {}

vk::Buffer e172vp::TexturedVertexObject::vertexBuffer() const {
    return m_vertexBuffer;
}

vk::Buffer e172vp::TexturedVertexObject::indexBuffer() const {
    return m_indexBuffer;
}

uint32_t e172vp::TexturedVertexObject::indexCount() const {
    return m_indexCount;
}

void e172vp::TexturedVertexObject::update(int)
{

}

std::vector<vk::DescriptorSet> e172vp::TexturedVertexObject::descriptorSets() {
    return std::vector<vk::DescriptorSet>();
}
