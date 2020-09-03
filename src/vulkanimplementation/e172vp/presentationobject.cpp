#include "presentationobject.h"

#include <iostream>
#include <fstream>
#include "tools/stringvector.h"
#include <math.h>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include "tools/buffer.h"
#include "../../engine/additional.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_vulkan.h>

e172vp::PresentationObject::PresentationObject(const std::string &assetFolder) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_window = SDL_CreateWindow("dfdf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_VULKAN);

    GraphicsObjectCreateInfo createInfo;
    createInfo.setRequiredExtensions(sdlExtensions(m_window));
    createInfo.setApplicationName("test-app");
    createInfo.setApplicationVersion(1);
    createInfo.setDebugEnabled(true);
    createInfo.setRequiredDeviceExtensions({ VK_KHR_SWAPCHAIN_EXTENSION_NAME });
    createInfo.setSubpassCount(2);
    createInfo.setSurfaceCreator([this](vk::Instance i, vk::SurfaceKHR *s) {
        VkSurfaceKHR ss;
        SDL_Vulkan_CreateSurface(m_window, i, &ss);
        *s = ss;
    });

    m_graphicsObject = GraphicsObject(createInfo);

    if(m_graphicsObject.debugEnabled())
        std::cout << "Used validation layers: " << StringVector::toString(m_graphicsObject.enabledValidationLayers()) << "\n";

    if(!m_graphicsObject.isValid())
        std::cout << "GRAPHICS OBJECT IS NOT CREATED BECAUSE OF FOLOWING ERRORS:\n\n";

    const auto errors = m_graphicsObject.pullErrors();
    if(errors.size())
        std::cerr << StringVector::toString(errors) << "\n";


    globalDescriptorSetLayout = DescriptorSetLayout::createUniformDSL(m_graphicsObject.logicalDevice(), 0);
    objectDescriptorSetLayout = DescriptorSetLayout::createUniformDSL(m_graphicsObject.logicalDevice(), 1);
    samplerDescriptorSetLayout = DescriptorSetLayout::createSamplerDSL(m_graphicsObject.logicalDevice(), 2);


    Buffer::createUniformBuffers<GlobalUniformBufferObject>(&m_graphicsObject, m_graphicsObject.swapChain().imageCount(), &uniformBuffers, &uniformBuffersMemory);
    Buffer::createUniformDescriptorSets<GlobalUniformBufferObject>(m_graphicsObject.logicalDevice(), m_graphicsObject.descriptorPool(), uniformBuffers, &globalDescriptorSetLayout, &uniformDescriptorSets);

    const std::vector<char> vertShaderCode = readFile(e172::Additional::constrainPath(assetFolder + "/shaders/vert_uniform.spv"));
    const std::vector<char> fragShaderCode = readFile(e172::Additional::constrainPath(assetFolder + "/shaders/frag_sampler.spv"));
    pipeline = new Pipeline(m_graphicsObject.logicalDevice(), m_graphicsObject.swapChainSettings().extent, m_graphicsObject.renderPass(), 0, { globalDescriptorSetLayout.descriptorSetLayoutHandle(), objectDescriptorSetLayout.descriptorSetLayoutHandle(), samplerDescriptorSetLayout.descriptorSetLayoutHandle() }, vertShaderCode, fragShaderCode, vk::PrimitiveTopology::eTriangleList);

    pipeline2 = new Pipeline(
                m_graphicsObject.logicalDevice(),
                m_graphicsObject.swapChainSettings().extent,
                m_graphicsObject.renderPass(),
                1,
                { globalDescriptorSetLayout.descriptorSetLayoutHandle() },
                readFile(e172::Additional::constrainPath(assetFolder + "/shaders/vert_linestrip.spv")),
                readFile(e172::Additional::constrainPath(assetFolder + "/shaders/frag_inter.spv")),
                vk::PrimitiveTopology::eLineStrip
                );

    createSyncObjects(m_graphicsObject.logicalDevice(), &imageAvailableSemaphore, &renderFinishedSemaphore);

    font = new Font(m_graphicsObject.logicalDevice(), m_graphicsObject.physicalDevice(), m_graphicsObject.commandPool(), m_graphicsObject.graphicsQueue(), e172::Additional::constrainPath(assetFolder + "/fonts/ZCOOL.ttf"), 128);

    elapsedFromStart.reset();
}

void e172vp::PresentationObject::present() {
    resetCommandBuffers(m_graphicsObject.commandPool().commandBufferVector(), m_graphicsObject.graphicsQueue(), m_graphicsObject.presentQueue());
    proceedCommandBuffers();

    uint32_t imageIndex = 0;
    vk::Result returnCode;


    returnCode = m_graphicsObject.logicalDevice().acquireNextImageKHR(m_graphicsObject.swapChain(), UINT64_MAX, imageAvailableSemaphore, {}, &imageIndex);
    if(returnCode != vk::Result::eSuccess)
        throw std::runtime_error("acquiring next image failed. code: " + vk::to_string(returnCode));

    auto currentImageCommandBuffer = m_graphicsObject.commandPool().commandBuffer(imageIndex);

    vk::Semaphore waitSemaphores[] = { imageAvailableSemaphore };
    vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };


    updateUniformBuffer(imageIndex);

    for(auto o : vertexObjects) {
        o->updateUbo(imageIndex);
    }

    vk::SubmitInfo submitInfo;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.setCommandBuffers(currentImageCommandBuffer);
    submitInfo.setSignalSemaphores(renderFinishedSemaphore);

    returnCode = m_graphicsObject.graphicsQueue().submit(1, &submitInfo, {});


    if (returnCode != vk::Result::eSuccess)
        throw std::runtime_error("failed to submit draw command buffer. code: " + vk::to_string(returnCode));

    vk::SwapchainKHR swapChains[] = { m_graphicsObject.swapChain() };

    vk::PresentInfoKHR presentInfo;
    presentInfo.setWaitSemaphores(renderFinishedSemaphore);
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    returnCode = m_graphicsObject.presentQueue().presentKHR(&presentInfo);
    if(returnCode != vk::Result::eSuccess)
        throw std::runtime_error("present failed. code: " + vk::to_string(returnCode));



    //for(auto o : pl2objects) {
    //    delete o;
    //}
    //pl2objects.clear();

}

void e172vp::PresentationObject::updateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    GlobalUniformBufferObject ubo;
    //ubo.offset = { std::cos(time * 0.2) * 0.2, std::sin(time * 0.2) * 0.2 };
    ubo.offset = { 0, 0 };
    ubo.scale = m_globalScale;
    ubo.currentTime = time;
    void* data;
    vkMapMemory(m_graphicsObject.logicalDevice(), uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(m_graphicsObject.logicalDevice(), uniformBuffersMemory[currentImage]);
}

void e172vp::PresentationObject::setGlobalScale(float scale) {
    m_globalScale = glm::scale(glm::mat4(1.), glm::vec3(scale));
}


bool e172vp::PresentationObject::isValid() const {
    return true;
}

std::vector<std::string> e172vp::PresentationObject::sdlExtensions(SDL_Window *window) {
    uint32_t extensionCount = 0;
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
    std::vector<const char *> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());

    std::vector<std::string> result(extensionCount);
    for(uint32_t i = 0; i < extensionCount; ++i) {
        result[i] = extensionNames[i];
    }
    return result;
}

void e172vp::PresentationObject::proceedCommandBuffers() {    
    for (size_t i = 0; i < m_graphicsObject.commandPool().commandBufferCount(); i++) {
        const auto commandBuffer = m_graphicsObject.commandPool().commandBuffer(i);
        const auto extent = m_graphicsObject.swapChainSettings().extent;

        vk::CommandBufferBeginInfo commandBufferBeginInfo;
        commandBuffer.begin(&commandBufferBeginInfo);

        const vk::ClearValue clearColor = vk::ClearColorValue(std::array<float, 4> {
                                                                  0x1a / 256.,
                                                                  0x00 / 256.,
                                                                  0x33 / 256.,
                                                                  0.4f
                                                              });

        vk::RenderPassBeginInfo renderPassInfo;
        renderPassInfo.renderPass = m_graphicsObject.renderPass().renderPathHandle();
        renderPassInfo.framebuffer = m_graphicsObject.renderPass().frameBuffer(i);
        renderPassInfo.renderArea.offset = vk::Offset2D();
        renderPassInfo.renderArea.extent = extent;
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vk::Viewport viewport;
        viewport.setX(0);
        viewport.setWidth(extent.width);
        viewport.setY(0);
        viewport.setHeight(extent.height);
        viewport.setMinDepth(0.0f);
        viewport.setMaxDepth(1.0f);

        commandBuffer.beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);
        commandBuffer.setViewport(0, 1, &viewport);


        commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline->handle());
        for(auto object : vertexObjects) {
            if(object->visible()) {
                vk::Buffer vb[] = { object->vertexBuffer() };
                vk::DeviceSize offsets[] = { 0 };
                commandBuffer.bindVertexBuffers(0, 1, vb, offsets);
                commandBuffer.bindIndexBuffer(object->indexBuffer(), 0, vk::IndexType::eUint32);

                commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline->pipelineLayout(), 0, { uniformDescriptorSets[i], object->descriptorSets()[i], object->textureDescriptorSets()[i] }, {});
                commandBuffer.drawIndexed(object->indexCount(), 1, 0, 0, 0);
            }
        }

        //pipeline2
        commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline2->handle());
        for(auto object : pl2objects) {
            if(object->visible()) {
                vk::Buffer vb[] = { object->vertexBuffer() };
                vk::DeviceSize offsets[] = { 0 };
                commandBuffer.bindVertexBuffers(0, 1, vb, offsets);
                commandBuffer.bindIndexBuffer(object->indexBuffer(), 0, vk::IndexType::eUint32);
                commandBuffer.drawIndexed(object->indexCount(), 1, 0, 0, 0);
            }
        }


        commandBuffer.endRenderPass();

        commandBuffer.end();
    }
}

void e172vp::PresentationObject::resetCommandBuffers(const std::vector<vk::CommandBuffer> &commandBuffers, const vk::Queue &graphicsQueue, const vk::Queue &presentQueue) {
    graphicsQueue.waitIdle();
    presentQueue.waitIdle();

    for(auto b : commandBuffers) {
        b.reset(vk::CommandBufferResetFlagBits::eReleaseResources);
    }
}

std::vector<char> e172vp::PresentationObject::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

e172vp::VertexObject *e172vp::PresentationObject::addVertexObject(const std::vector<e172vp::Vertex> &vertices, const std::vector<uint32_t> &indices) {
    const auto r = new VertexObject(&m_graphicsObject, m_graphicsObject.swapChain().imageCount(), &objectDescriptorSetLayout, &samplerDescriptorSetLayout, vertices, indices, font->character('F').imageView());
    vertexObjects.push_back(r);
    return r;
}

e172vp::VertexObject *e172vp::PresentationObject::addVertexObject2(const std::vector<e172vp::Vertex> &vertices, const std::vector<uint32_t> &indices) {
    const auto r = new VertexObject(&m_graphicsObject, 0, &objectDescriptorSetLayout, &samplerDescriptorSetLayout, vertices, indices, vk::ImageView());
    pl2objects.push_back(r);
    return r;
}

e172vp::VertexObject *e172vp::PresentationObject::addCharacter(char c) {
    const static std::vector<e172vp::Vertex> v = {
        { { -0.1f, -0.1f, 0 }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.1f, -0.1f, 0 }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.1f, 0.1f, 0 }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.1f, 0.1f, 0 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } }
    };
    const static std::vector<uint32_t> i = {
        0, 1, 2,
        2, 3, 0
    };

    const auto r = new VertexObject(&m_graphicsObject, m_graphicsObject.swapChain().imageCount(), &objectDescriptorSetLayout, &samplerDescriptorSetLayout, v, i, font->character(c).imageView());
    vertexObjects.push_back(r);
    return r;
}


//void e172vp::PresentationObject::singlePointPresentation(const glm::vec3 &point, uint32_t color, const glm::mat4 model) {
//    const static std::vector<e172vp::Vertex> v = {
//        { { -0.01f, -0.01f, 0 }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
//        { { 0.01f, -0.01f, 0 }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
//        { { 0.01f, 0.01f, 0 }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
//        { { -0.01f, 0.01f, 0 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } }
//    };
//    const static std::vector<uint32_t> i = {
//        0, 1, 2,
//        2, 3, 0
//    };
//    singleVertexObjectPresentation(v, i);
//}

e172vp::VertexObject *e172vp::PresentationObject::addVertexObject(const e172vp::Mesh &mesh) {
    return addVertexObject(Vertex::fromGlm(mesh.vertices, mesh.uvMap), mesh.vertexIndices);
}

bool e172vp::PresentationObject::removeVertexObject(e172vp::VertexObject *vertexObject) {
    const auto it = std::find(vertexObjects.begin(), vertexObjects.end(), vertexObject);
    if(it != vertexObjects.end()) {
        delete vertexObject;
        vertexObjects.erase(it);
        return true;
    }
    return true;
}

void e172vp::PresentationObject::createSyncObjects(const vk::Device &logicDevice, vk::Semaphore *imageAvailableSemaphore, vk::Semaphore *renderFinishedSemaphore) {
    vk::SemaphoreCreateInfo semaphoreInfo;
    if (
            logicDevice.createSemaphore(&semaphoreInfo, nullptr, imageAvailableSemaphore) != vk::Result::eSuccess ||
            logicDevice.createSemaphore(&semaphoreInfo, nullptr, renderFinishedSemaphore) != vk::Result::eSuccess
            )
        throw std::runtime_error("failed to create synchronization objects for a frame!");
}

e172vp::GraphicsObject e172vp::PresentationObject::graphicsObject() const { return m_graphicsObject; }
