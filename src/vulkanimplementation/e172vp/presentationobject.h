#ifndef RENDERER_H
#define RENDERER_H

#include "graphicsobject/graphicsobject.h"
#define GLM_FORCE_RADIANS
#include "vertex.h"
#include <list>
#include "descriptorsetlayout.h"
#include "tools/mesh.h"
#include "vertexobjects/abstractvertexobject.h"


namespace e172vp {

class Pipeline;

class PresentationObject {
    GraphicsObject *m_graphicsObject = nullptr;

    vk::Semaphore imageAvailableSemaphore;
    vk::Semaphore renderFinishedSemaphore;

    e172vp::DescriptorSetLayout globalDescriptorSetLayout;
    e172vp::DescriptorSetLayout objectDescriptorSetLayout;
    e172vp::DescriptorSetLayout samplerDescriptorSetLayout;

    std::vector<vk::Buffer> uniformBuffers;
    std::vector<vk::DeviceMemory> uniformBuffersMemory;
    std::vector<vk::DescriptorSet> uniformDescriptorSets;

    vk::Image m_uiImage;
    vk::DeviceMemory m_uiImageMemory;

    glm::mat4 m_globalScale = glm::mat4(1.);

    struct GlobalUniformBufferObject {
        float time;
        glm::vec2 offset;
        glm::mat4 scale;
    };

    std::list<AbstractVertexObject*> vertexObjects;

    void proceedCommandBuffers();
    static void resetCommandBuffers(const std::vector<vk::CommandBuffer> &commandBuffers, const vk::Queue &graphicsQueue, const vk::Queue &presentQueue);
    static void createSyncObjects(const vk::Device &logicDevice, vk::Semaphore *imageAvailableSemaphore, vk::Semaphore *renderFinishedSemaphore);
    void updateUniformBuffer(uint32_t currentImage);

public:
    enum PipelineDescriptorSetLayouts {
        NoAnyDSL = 0,
        GlobalDSL = 1,
        PerObjectDSL = 2,
        SamplerDSL = 4
    };
    friend inline PipelineDescriptorSetLayouts operator |(PipelineDescriptorSetLayouts e0, PipelineDescriptorSetLayouts e1) {
        return static_cast<PipelineDescriptorSetLayouts>(static_cast<uint64_t>(e0) | static_cast<uint64_t>(e1));
    }

    PresentationObject(const GraphicsObjectCreateInfo &graphicsInstanceCreateInfo);

    template<typename T, typename ...Args>
    T *addVertexObject(const Args&... args) {
        const auto r = new T(args...);
        r->m_graphicsObject = m_graphicsObject;
        r->initialize(m_graphicsObject, m_graphicsObject->swapChain().imageCount(), &objectDescriptorSetLayout, &samplerDescriptorSetLayout);
        vertexObjects.push_back(r);
        return r;
    }

    bool removeVertexObject(AbstractVertexObject *vertexObject);

    void present();

    void setGlobalScale(float scale);

    e172vp::Pipeline *createPipeline(int subpass, PipelineDescriptorSetLayouts includedDescriptorSetLayouts, const std::vector<char> &vertexShader, const std::vector<char> &fragmentShader, vk::PrimitiveTopology topology);

    bool isValid() const;
    GraphicsObject *graphicsObject() const;
    ~PresentationObject();

    void updateUiImage(size_t w, size_t h, void *data);
    void setUiImage(const vk::Image &uiImage);
};

}

#endif // RENDERER_H
