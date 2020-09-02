#ifndef RENDERER_H
#define RENDERER_H

#include "graphicsobject.h"
#define GLM_FORCE_RADIANS
#include <SDL2/SDL.h>
#include "time/elapsedtimer.h"
#include "vertex.h"
#include <list>
#include "vertexobject.h"
#include "descriptorsetlayout.h"
#include "tools/mesh.h"
#include "pipeline.h"

#include "font.h"

namespace e172vp {


class PresentationObject {
    GraphicsObject m_graphicsObject;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    SDL_Window *m_window = nullptr;

    vk::Semaphore imageAvailableSemaphore;
    vk::Semaphore renderFinishedSemaphore;

    Pipeline *pipeline = nullptr;

    Pipeline *pipeline2 = nullptr;

    vk::Buffer vertexBuffer;
    vk::DeviceMemory vertexBufferMemory;
    vk::Buffer indexBuffer;
    vk::DeviceMemory indexBufferMemory;

    e172vp::ElapsedTimer elapsedFromStart;

    e172vp::DescriptorSetLayout globalDescriptorSetLayout;
    e172vp::DescriptorSetLayout objectDescriptorSetLayout;
    e172vp::DescriptorSetLayout samplerDescriptorSetLayout;


    std::vector<vk::Buffer> uniformBuffers;
    std::vector<vk::DeviceMemory> uniformBuffersMemory;
    std::vector<vk::DescriptorSet> uniformDescriptorSets;

    Font *font = nullptr;
    glm::mat4 m_globalScale = glm::mat4(1.);

    struct GlobalUniformBufferObject {
        glm::vec2 offset;
        glm::mat4 scale;
        float currentTime;
    };

    std::list<VertexObject*> vertexObjects;


    std::list<VertexObject*> pl2objects;
public:
    bool isValid() const;
    static std::vector<std::string> sdlExtensions(SDL_Window *window);

    void proceedCommandBuffers();

    static void resetCommandBuffers(const std::vector<vk::CommandBuffer> &commandBuffers, const vk::Queue &graphicsQueue, const vk::Queue &presentQueue);
    static void createSyncObjects(const vk::Device &logicDevice, vk::Semaphore *imageAvailableSemaphore, vk::Semaphore *renderFinishedSemaphore);

    static std::vector<char> readFile(const std::string &filename);

    VertexObject *addVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
    VertexObject *addVertexObject2(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

    VertexObject *addCharacter(char c);


//    void singlePointPresentation(const glm::vec3 &point, uint32_t color, const glm::mat4 model);



    VertexObject *addVertexObject(const Mesh &mesh);
    bool removeVertexObject(VertexObject *vertexObject);
    PresentationObject(const std::string &assetFolder);

    void present();
    void updateUniformBuffer(uint32_t currentImage);
    void setGlobalScale(float scale);

    GraphicsObject graphicsObject() const;
};

}

#endif // RENDERER_H
