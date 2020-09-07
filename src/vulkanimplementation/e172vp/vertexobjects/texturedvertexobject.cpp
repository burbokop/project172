#include "texturedvertexobject.h"

#include "../tools/buffer.h"
#include "../graphicsobject/graphicsobject.h"
#include "../font.h"

int e172vp::TexturedVertexObject::textureWidth() const {
    return m_textureWidth;
}

int e172vp::TexturedVertexObject::textureHeight() const {
    return m_textureHeight;
}

e172vp::TexturedVertexObject::TexturedVertexObject(int textureWidth, int textureHeight) {
    m_textureWidth = textureWidth;
    m_textureHeight = textureHeight;
}


void e172vp::TexturedVertexObject::initialize(const e172vp::GraphicsObject *graphicsObject, int frameCount, const e172vp::DescriptorSetLayout *objectDSL, const e172vp::DescriptorSetLayout *samplerDSL) {
    Buffer::createVertexBuffer(graphicsObject, m_vertices, &m_vertexBuffer, &m_vertexBufferMemory);
    Buffer::createIndexBuffer(graphicsObject, m_indices, &m_indexBuffer, &m_indexBufferMemory);

    Buffer::createUniformBuffer<ubo>(graphicsObject, &m_uniformBuffer, &m_uniformBufferMemory);

    vk::DescriptorSet tmpDescriptorSet;
    Buffer::createUniformDescriptorSet<ubo>(graphicsObject->logicalDevice(), graphicsObject->descriptorPool(), m_uniformBuffer, objectDSL, &tmpDescriptorSet);
    m_descriptorSets.push_back(tmpDescriptorSet);

    if(m_textureWidth > 0 && m_textureHeight > 0) {
        Font::createImage(graphicsObject->logicalDevice(), graphicsObject->physicalDevice(), m_textureWidth, m_textureHeight, vk::Format::eR8G8B8A8Srgb, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, vk::MemoryPropertyFlagBits::eDeviceLocal, &m_image, &m_imageMemory);
        m_imageView = SwapChain::createImageView(graphicsObject->logicalDevice(), m_image, vk::Format::eR8G8B8A8Srgb);
    }

    Buffer::createSamplerDescriptorSet(graphicsObject->logicalDevice(), graphicsObject->descriptorPool(), m_imageView, graphicsObject->sampler(), samplerDSL, &tmpDescriptorSet);
    m_descriptorSets.push_back(tmpDescriptorSet);
}

e172vp::TexturedVertexObject::~TexturedVertexObject()
{
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


vk::Buffer e172vp::TexturedVertexObject::vertexBuffer() const {
    return m_vertexBuffer;
}

vk::Buffer e172vp::TexturedVertexObject::indexBuffer() const {
    return m_indexBuffer;
}

uint32_t e172vp::TexturedVertexObject::indexCount() const {
    return m_indices.size();
}

void e172vp::TexturedVertexObject::update(int) {
    ubo __ubo;
    __ubo.model = m_translation * m_rotation * m_scale;

    void* data;
    vkMapMemory(graphicsObject()->logicalDevice(), m_uniformBufferMemory, 0, sizeof(ubo), 0, &data);
    memcpy(data, &__ubo, sizeof(ubo));
    vkUnmapMemory(graphicsObject()->logicalDevice(), m_uniformBufferMemory);
}

std::vector<vk::DescriptorSet> e172vp::TexturedVertexObject::descriptorSets() {
    return std::vector<vk::DescriptorSet>();
}
