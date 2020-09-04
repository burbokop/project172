
#include "externaltexvertexobject.h"

#include "../tools/buffer.h"
#include "../graphicsobject/graphicsobject.h"


e172vp::ExternalTexVertexObject::ExternalTexVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, const vk::ImageView &imageView) {
    m_vertices = vertices;
    m_indices = indices;
    m_imageView = imageView;
}

void e172vp::ExternalTexVertexObject::initialize(const GraphicsObject *graphicsObject, int, const DescriptorSetLayout *objectDSL, const DescriptorSetLayout *samplerDSL) {
    Buffer::createVertexBuffer(graphicsObject, m_vertices, &m_vertexBuffer, &m_vertexBufferMemory);
    Buffer::createIndexBuffer(graphicsObject, m_indices, &m_indexBuffer, &m_indexBufferMemory);

    Buffer::createUniformBuffer<ubo>(graphicsObject, &m_uniformBuffer, &m_uniformBufferMemory);

    vk::DescriptorSet tmpDescriptorSet;
    Buffer::createUniformDescriptorSet<ubo>(graphicsObject->logicalDevice(), graphicsObject->descriptorPool(), m_uniformBuffer, objectDSL, &tmpDescriptorSet);
    m_descriptorSets.push_back(tmpDescriptorSet);


    if(m_imageView) {
        vk::DescriptorSet tmpDescriptorSet;
        Buffer::createSamplerDescriptorSet(graphicsObject->logicalDevice(), graphicsObject->descriptorPool(), m_imageView, graphicsObject->sampler(), samplerDSL, &tmpDescriptorSet);
        m_descriptorSets.push_back(tmpDescriptorSet);
    }
}

vk::Buffer e172vp::ExternalTexVertexObject::vertexBuffer() const {
    return m_vertexBuffer;
}

vk::Buffer e172vp::ExternalTexVertexObject::indexBuffer() const {
    return m_indexBuffer;
}

uint32_t e172vp::ExternalTexVertexObject::indexCount() const {
    return m_indices.size();
}



void e172vp::ExternalTexVertexObject::update(int) {
    ubo __ubo;
    __ubo.model = m_translation * m_rotation * m_scale;

    void* data;
    vkMapMemory(graphicsObject()->logicalDevice(), m_uniformBufferMemory, 0, sizeof(ubo), 0, &data);
    memcpy(data, &__ubo, sizeof(ubo));
    vkUnmapMemory(graphicsObject()->logicalDevice(), m_uniformBufferMemory);
}

std::vector<vk::DescriptorSet> e172vp::ExternalTexVertexObject::descriptorSets() {
    return m_descriptorSets;
}


glm::mat4 e172vp::ExternalTexVertexObject::rotation() const {
    return m_rotation;
}

void e172vp::ExternalTexVertexObject::setRotation(const glm::mat4 &rotation) {
    m_rotation = rotation;
}

glm::mat4 e172vp::ExternalTexVertexObject::translation() const {
    return m_translation;
}

void e172vp::ExternalTexVertexObject::setTranslation(const glm::mat4 &translation)
{
    m_translation = translation;
}

glm::mat4 e172vp::ExternalTexVertexObject::scale() const
{
    return m_scale;
}

void e172vp::ExternalTexVertexObject::setScale(const glm::mat4 &scale)
{
    m_scale = scale;
}


e172vp::ExternalTexVertexObject::~ExternalTexVertexObject() {
    if(m_vertexBuffer)
        graphicsObject()->logicalDevice().destroyBuffer(m_vertexBuffer);
    if(m_vertexBufferMemory)
        graphicsObject()->logicalDevice().freeMemory(m_vertexBufferMemory);
    if(m_indexBuffer)
        graphicsObject()->logicalDevice().destroyBuffer(m_indexBuffer);
    if(m_indexBufferMemory)
        graphicsObject()->logicalDevice().freeMemory(m_indexBufferMemory);

    if(m_uniformBuffer)
        graphicsObject()->logicalDevice().destroyBuffer(m_uniformBuffer);
    if(m_uniformBufferMemory)
        graphicsObject()->logicalDevice().freeMemory(m_uniformBufferMemory);


    if(m_descriptorSets.size() > 0)
        graphicsObject()->logicalDevice().freeDescriptorSets(graphicsObject()->descriptorPool(), m_descriptorSets);
}
