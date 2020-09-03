#ifndef ABSTRACTVERTEXOBJECT_H
#define ABSTRACTVERTEXOBJECT_H

#include <vulkan/vulkan.hpp>

namespace e172vp {

class GraphicsObject;
class PresentationObject;
class Pipeline;

class AbstractVertexObject {
    friend PresentationObject;
    bool m_visible = true;
    bool m_bindGlobalDescriptorSet;
    GraphicsObject *m_graphicsObject = nullptr;
    Pipeline *m_pipeline = nullptr;
public:
    AbstractVertexObject();

    virtual vk::Buffer vertexBuffer() const = 0;
    virtual vk::Buffer indexBuffer() const = 0;
    virtual uint32_t indexCount() const = 0;
    virtual void update(int frameIndex) = 0;
    virtual std::vector<vk::DescriptorSet> descriptorSets() = 0;
    virtual ~AbstractVertexObject();
    virtual void initialize(
            GraphicsObject *graphicsObject,
            int frameCount,
            const vk::DescriptorSetLayout globalDSL,
            const vk::DescriptorSetLayout objectDSL,
            const vk::DescriptorSetLayout samplerDSL
            ) = 0;

    bool visible() const;
    void setVisible(bool visible);
    bool bindGlobalDescriptorSet() const;
    void setBindGlobalDescriptorSet(bool bindGlobalDescriptorSet);
    Pipeline *pipeline() const;
    void setPipeline(Pipeline *pipeline);
};

}
#endif // ABSTRACTVERTEXOBJECT_H
