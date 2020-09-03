#include "vertexobject.h"

#include "../tools/buffer.h"
#include "../graphicsobject/graphicsobject.h"

vk::DescriptorSet e172vp::VertexObject::descriptorSet() const {
    return m_descriptorSet;
}

e172vp::VertexObject::VertexObject(const e172vp::GraphicsObject *graphicsObject, size_t imageCount, const DescriptorSetLayout *descriptorSetLayout, const DescriptorSetLayout *samplerDescriptorSetLayout, const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, const vk::ImageView &imageView) {
    m_graphicsObject = const_cast<GraphicsObject*>(graphicsObject);
    Buffer::createVertexBuffer(graphicsObject, vertices, &m_vertexBuffer, &m_vertexBufferMemory);
    Buffer::createIndexBuffer(graphicsObject, indices, &m_indexBuffer, &m_indexBufferMemory);

    if(imageCount > 0) {
        Buffer::createUniformBuffer<ubo>(graphicsObject, &m_uniformBuffer, &m_uniformBufferMemory);
        Buffer::createUniformDescriptorSet<ubo>(graphicsObject->logicalDevice(), graphicsObject->descriptorPool(), m_uniformBuffer, descriptorSetLayout, &m_descriptorSet);
        if(imageView) {
            Buffer::createSamplerDescriptorSet(graphicsObject->logicalDevice(), graphicsObject->descriptorPool(), imageView, graphicsObject->sampler(), samplerDescriptorSetLayout, &m_textureDescriptorSet);
        }
    }
    m_indexCount = indices.size();
}

e172vp::GraphicsObject *e172vp::VertexObject::graphicsObject() const {
    return m_graphicsObject;
}

vk::Buffer e172vp::VertexObject::vertexBuffer() const {
    return m_vertexBuffer;
}

vk::Buffer e172vp::VertexObject::indexBuffer() const {
    return m_indexBuffer;
}

uint32_t e172vp::VertexObject::indexCount() const {
    return m_indexCount;
}

void e172vp::VertexObject::updateTexture(int w, int h, void *data) const {
    //if(m_textureDescriptorSets)
}

void e172vp::VertexObject::setVertices(const std::vector<e172vp::Vertex> &vertices) {
    Buffer::updateVertexBuffer(m_graphicsObject, vertices, m_vertexBuffer);
}

void e172vp::VertexObject::updateUbo(int imageIndex) {
    ubo __ubo;
    __ubo.model = m_translation * m_rotation * m_scale;

    void* data;
    vkMapMemory(m_graphicsObject->logicalDevice(), m_uniformBufferMemory, 0, sizeof(ubo), 0, &data);
    memcpy(data, &__ubo, sizeof(ubo));
    vkUnmapMemory(m_graphicsObject->logicalDevice(), m_uniformBufferMemory);
}

glm::mat4 e172vp::VertexObject::rotation() const
{
    return m_rotation;
}

void e172vp::VertexObject::setRotation(const glm::mat4 &rotation)
{
    m_rotation = rotation;
}

glm::mat4 e172vp::VertexObject::translation() const
{
    return m_translation;
}

void e172vp::VertexObject::setTranslation(const glm::mat4 &translation)
{
    m_translation = translation;
}

glm::mat4 e172vp::VertexObject::scale() const
{
    return m_scale;
}

void e172vp::VertexObject::setScale(const glm::mat4 &scale)
{
    m_scale = scale;
}

vk::DescriptorSet e172vp::VertexObject::textureDescriptorSet() const {
    return m_textureDescriptorSet;
}

bool e172vp::VertexObject::visible() const {
    return m_visible;
}

void e172vp::VertexObject::setVisible(bool visible) {
    m_visible = visible;
}


e172vp::VertexObject::~VertexObject() {
    if(m_vertexBuffer)
        m_graphicsObject->logicalDevice().destroyBuffer(m_vertexBuffer);
    if(m_vertexBufferMemory)
        m_graphicsObject->logicalDevice().freeMemory(m_vertexBufferMemory);
    if(m_indexBuffer)
        m_graphicsObject->logicalDevice().destroyBuffer(m_indexBuffer);
    if(m_indexBufferMemory)
        m_graphicsObject->logicalDevice().freeMemory(m_indexBufferMemory);

    if(m_uniformBuffer)
        m_graphicsObject->logicalDevice().destroyBuffer(m_uniformBuffer);
    if(m_uniformBufferMemory)
        m_graphicsObject->logicalDevice().freeMemory(m_uniformBufferMemory);

    if(m_descriptorSet)
        m_graphicsObject->logicalDevice().freeDescriptorSets(m_graphicsObject->descriptorPool(), m_descriptorSet);
}
