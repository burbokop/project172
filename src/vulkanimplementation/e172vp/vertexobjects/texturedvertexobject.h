#ifndef TEXTUREDVERTEXOBJECT_H
#define TEXTUREDVERTEXOBJECT_H

#include "abstractvertexobject.h"
#include "../vertex.h"
#include <glm/glm.hpp>

namespace e172vp {

class TexturedVertexObject : public AbstractVertexObject {
    struct ubo { glm::mat4 model; };

    glm::mat4 m_rotation = glm::mat4(1);
    glm::mat4 m_translation = glm::mat4(1);
    glm::mat4 m_scale = glm::mat4(1);

    vk::Buffer m_vertexBuffer;
    vk::DeviceMemory m_vertexBufferMemory;
    vk::Buffer m_indexBuffer;
    vk::DeviceMemory m_indexBufferMemory;
    vk::Buffer m_uniformBuffer;
    vk::DeviceMemory m_uniformBufferMemory;

    std::vector<vk::DescriptorSet> m_descriptorSets;


    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;

    vk::Image m_image;
    vk::DeviceMemory m_imageMemory;
    vk::ImageView m_imageView;

    int m_textureWidth;
    int m_textureHeight;
public:
    TexturedVertexObject(int textureWidth, int textureHeight);

    ~TexturedVertexObject();

    // AbstractVertexObject interface
public:
    virtual void initialize(const GraphicsObject *graphicsObject, int frameCount, const DescriptorSetLayout *objectDSL, const DescriptorSetLayout *samplerDSL) override;
    virtual vk::Buffer vertexBuffer() const override;
    virtual vk::Buffer indexBuffer() const override;
    virtual uint32_t indexCount() const override;
    virtual void update(int) override;
    virtual std::vector<vk::DescriptorSet> descriptorSets() override;    
    int textureWidth() const;
    int textureHeight() const;
};
}
#endif // TEXTUREDVERTEXOBJECT_H
