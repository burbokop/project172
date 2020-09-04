#ifndef TEXTUREDVERTEXOBJECT_H
#define TEXTUREDVERTEXOBJECT_H

#include "abstractvertexobject.h"

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
    uint32_t m_indexCount;

    vk::Buffer m_uniformBuffer;
    vk::DeviceMemory m_uniformBufferMemory;

    vk::Image m_texture;
    vk::ImageView m_imageView;

    std::vector<vk::DescriptorSet> m_descriptorSets;



public:
    TexturedVertexObject();

    // AbstractVertexObject interface
public:
    virtual vk::Buffer vertexBuffer() const override;
    virtual vk::Buffer indexBuffer() const override;
    virtual uint32_t indexCount() const override;
    virtual void update(int) override;
    virtual std::vector<vk::DescriptorSet> descriptorSets() override;
};
}
#endif // TEXTUREDVERTEXOBJECT_H
