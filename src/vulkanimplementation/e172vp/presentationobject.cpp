#include "font.h"
#include "pipeline.h"
#include "presentationobject.h"

#include <iostream>
#include "tools/stringvector.h"
#include <math.h>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include "tools/buffer.h"

e172vp::PresentationObject::PresentationObject(const GraphicsObjectCreateInfo &graphicsInstanceCreateInfo) {
    m_graphicsObject = new GraphicsObject(graphicsInstanceCreateInfo);

    if(m_graphicsObject->debugEnabled())
        std::cout << "Used validation layers: " << StringVector::toString(m_graphicsObject->enabledValidationLayers()) << "\n";

    if(!m_graphicsObject->isValid())
        std::cout << "GRAPHICS OBJECT IS NOT CREATED BECAUSE OF FOLOWING ERRORS:\n\n";

    const auto errors = m_graphicsObject->pullErrors();
    if(errors.size())
        std::cerr << StringVector::toString(errors) << "\n";


    globalDescriptorSetLayout = DescriptorSetLayout::createUniformDSL(m_graphicsObject->logicalDevice(), 0);
    objectDescriptorSetLayout = DescriptorSetLayout::createUniformDSL(m_graphicsObject->logicalDevice(), 1);
    samplerDescriptorSetLayout = DescriptorSetLayout::createSamplerDSL(m_graphicsObject->logicalDevice(), 2);

    Buffer::createUniformBuffers<GlobalUniformBufferObject>(m_graphicsObject, m_graphicsObject->swapChain().imageCount(), &uniformBuffers, &uniformBuffersMemory);
    Buffer::createUniformDescriptorSets<GlobalUniformBufferObject>(m_graphicsObject->logicalDevice(), m_graphicsObject->descriptorPool(), uniformBuffers, &globalDescriptorSetLayout, &uniformDescriptorSets);

    createSyncObjects(m_graphicsObject->logicalDevice(), &imageAvailableSemaphore, &renderFinishedSemaphore);


}

e172vp::PresentationObject::~PresentationObject() {
    delete m_graphicsObject;
}

void e172vp::PresentationObject::updateUiImage(size_t w, size_t h, void *data) {
    e172vp::Font::updateTextureImage(m_graphicsObject->logicalDevice(), m_graphicsObject->physicalDevice(), m_graphicsObject->commandPool(), m_graphicsObject->graphicsQueue(), data, w, h, vk::Format::eR8G8B8A8Srgb, m_uiImage);
}

void e172vp::PresentationObject::present() {
    resetCommandBuffers(m_graphicsObject->commandPool().commandBufferVector(), m_graphicsObject->graphicsQueue(), m_graphicsObject->presentQueue());
    proceedCommandBuffers();

    uint32_t imageIndex = 0;
    vk::Result returnCode;


    returnCode = m_graphicsObject->logicalDevice().acquireNextImageKHR(m_graphicsObject->swapChain(), UINT64_MAX, imageAvailableSemaphore, {}, &imageIndex);
    if(returnCode != vk::Result::eSuccess)
        throw std::runtime_error("acquiring next image failed. code: " + vk::to_string(returnCode));

    auto currentImageCommandBuffer = m_graphicsObject->commandPool().commandBuffer(imageIndex);

    vk::Semaphore waitSemaphores[] = { imageAvailableSemaphore };
    vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };


    updateUniformBuffer(imageIndex);

    for(auto o : vertexObjects) {
        o->update(imageIndex);
    }

    vk::SubmitInfo submitInfo;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.setCommandBuffers(currentImageCommandBuffer);
    submitInfo.setSignalSemaphores(renderFinishedSemaphore);

    returnCode = m_graphicsObject->graphicsQueue().submit(1, &submitInfo, {});


    if (returnCode != vk::Result::eSuccess)
        throw std::runtime_error("failed to submit draw command buffer. code: " + vk::to_string(returnCode));

    vk::SwapchainKHR swapChains[] = { m_graphicsObject->swapChain() };

    vk::PresentInfoKHR presentInfo;
    presentInfo.setWaitSemaphores(renderFinishedSemaphore);
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    returnCode = m_graphicsObject->presentQueue().presentKHR(&presentInfo);
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
    ubo.offset = { std::cos(time * 0.2) * 0.2, std::sin(time * 0.2) * 0.2 };
    ubo.offset = { 0, 0 };
    ubo.scale = m_globalScale;
    ubo.time = time;
    void* data;
    vkMapMemory(m_graphicsObject->logicalDevice(), uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(m_graphicsObject->logicalDevice(), uniformBuffersMemory[currentImage]);
}

void e172vp::PresentationObject::setGlobalScale(float scale) {
    m_globalScale = glm::scale(glm::mat4(1.), glm::vec3(scale));
}

e172vp::Pipeline *e172vp::PresentationObject::createPipeline(int subpass, e172vp::PresentationObject::PipelineDescriptorSetLayouts includedDescriptorSetLayouts, const std::vector<char> &vertexShader, const std::vector<char> &fragmentShader, vk::PrimitiveTopology topology) {
    std::vector<vk::DescriptorSetLayout> dslVector;

    if(includedDescriptorSetLayouts & GlobalDSL) {
        dslVector.push_back(globalDescriptorSetLayout.descriptorSetLayoutHandle());
    }

    if(includedDescriptorSetLayouts & PerObjectDSL) {
        dslVector.push_back(objectDescriptorSetLayout.descriptorSetLayoutHandle());
    }

    if(includedDescriptorSetLayouts & SamplerDSL) {
        dslVector.push_back(samplerDescriptorSetLayout.descriptorSetLayoutHandle());
    }

    return new Pipeline(m_graphicsObject->logicalDevice(), m_graphicsObject->swapChainSettings().extent, m_graphicsObject->renderPass(), subpass, dslVector, vertexShader, fragmentShader, topology);
}

bool e172vp::PresentationObject::isValid() const {
    return true;
}

void e172vp::PresentationObject::setUiImage(const vk::Image &uiImage) {
    m_uiImage = uiImage;
}

void e172vp::PresentationObject::proceedCommandBuffers() {
    for (size_t i = 0; i < m_graphicsObject->commandPool().commandBufferCount(); i++) {
        const auto commandBuffer = m_graphicsObject->commandPool().commandBuffer(i);
        const auto extent = m_graphicsObject->swapChainSettings().extent;

        vk::CommandBufferBeginInfo commandBufferBeginInfo;
        commandBuffer.begin(&commandBufferBeginInfo);

        const vk::ClearValue clearColor = vk::ClearColorValue(std::array<float, 4> {
                                                                  0x1a / 256.,
                                                                  0x00 / 256.,
                                                                  0x33 / 256.,
                                                                  0.4f
                                                              });

        vk::RenderPassBeginInfo renderPassInfo;
        renderPassInfo.renderPass = m_graphicsObject->renderPass().renderPathHandle();
        renderPassInfo.framebuffer = m_graphicsObject->renderPass().frameBuffer(i);
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

        for(auto object : vertexObjects) {
            if(object->visible()) {
                commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, object->pipeline()->handle());
                vk::Buffer vb[] = { object->vertexBuffer() };
                vk::DeviceSize offsets[] = { 0 };
                commandBuffer.bindVertexBuffers(0, 1, vb, offsets);
                commandBuffer.bindIndexBuffer(object->indexBuffer(), 0, vk::IndexType::eUint32);

                //MERGING DESCRIPTOR SETS
                std::vector<vk::DescriptorSet> dsa;
                if(object->bindGlobalDescriptorSet()) {
                    dsa.push_back(uniformDescriptorSets[i]);
                }
                const auto dsaOffset = dsa.size();
                const auto odsa = object->descriptorSets();
                dsa.resize(dsaOffset + odsa.size());
                for(size_t i = 0; i < odsa.size(); ++i) {
                    dsa[i + dsaOffset] = odsa[i];
                }
                //MERGING DESCRIPTOR SETS END

                if(dsa.size() > 0) {
                    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, object->pipeline()->pipelineLayout(), 0, dsa, {});
                }
                commandBuffer.drawIndexed(object->indexCount(), 1, 0, 0, 0);
            }
        }

        vk::ImageBlit region;
        commandBuffer.blitImage(m_uiImage, vk::ImageLayout::eTransferSrcOptimal, m_graphicsObject->swapChain().image(i), vk::ImageLayout::eTransferDstOptimal, { region }, vk::Filter::eLinear);

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


bool e172vp::PresentationObject::removeVertexObject(AbstractVertexObject *vertexObject) {
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

e172vp::GraphicsObject *e172vp::PresentationObject::graphicsObject() const { return m_graphicsObject; }
