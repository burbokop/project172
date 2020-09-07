#ifndef VERTEXOBJECT_H
#define VERTEXOBJECT_H

#include "../vertex.h"
#include "../descriptorsetlayout.h"

#include "abstractvertexobject.h"

namespace e172vp {


class ExternalTexVertexObject : public AbstractVertexObject {
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
    vk::ImageView m_imageView;
public:
    ExternalTexVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, const vk::ImageView &imageView);
    ~ExternalTexVertexObject();


    void setVertices(const std::vector<Vertex> &vertices);
    glm::mat4 rotation() const;
    void setRotation(const glm::mat4 &rotation);
    glm::mat4 translation() const;
    void setTranslation(const glm::mat4 &translation);
    glm::mat4 scale() const;
    void setScale(const glm::mat4 &scale);

    // AbstractVertexObject interface
public:
    virtual vk::Buffer vertexBuffer() const override;
    virtual vk::Buffer indexBuffer() const override;
    virtual uint32_t indexCount() const override;
    virtual void update(int) override;
    virtual std::vector<vk::DescriptorSet> descriptorSets() override;
    virtual void initialize(const GraphicsObject *graphicsObject, int, const DescriptorSetLayout *objectDSL, const DescriptorSetLayout *samplerDSL) override;
};
}
#endif // VERTEXOBJECT_H
