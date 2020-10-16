#include "bootstrapobject.h"

#include <SDL2/SDL_vulkan.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <src/additional.h>

e172vp::PresentationObject * e172vp::BootstrapObject::presentationObject() const {
    return m_presentationObject;
}

e172vp::ExternalTexVertexObject *e172vp::BootstrapObject::addExternalTexVertexObject(const std::vector<e172vp::Vertex> &vertices, const std::vector<uint32_t> &indices) {
    auto obj = m_presentationObject->addVertexObject<ExternalTexVertexObject>(vertices, indices, font->character('G').imageView());
    obj->setPipeline(pipeline);
    obj->setBindGlobalDescriptorSet(true);
    return obj;
}

e172vp::ExternalTexVertexObject *e172vp::BootstrapObject::addExternalTexVertexObject(const e172vp::Mesh &mesh) {
    auto obj = m_presentationObject->addVertexObject<ExternalTexVertexObject>(Vertex::fromGlm(mesh.vertices, mesh.uvMap), mesh.vertexIndices, font->character('G').imageView());
    obj->setPipeline(pipeline);
    obj->setBindGlobalDescriptorSet(true);
    return obj;
}

e172vp::WireVertexObject *e172vp::BootstrapObject::addWireVertexObject(const std::vector<e172vp::Vertex> &vertices, const std::vector<uint32_t> &indices) {
    auto obj = m_presentationObject->addVertexObject<WireVertexObject>(vertices, indices);
    obj->setPipeline(pipeline2);
    return obj;
}

void e172vp::BootstrapObject::removeVertexObject(e172vp::AbstractVertexObject *object) {
    m_presentationObject->removeVertexObject(object);
}

std::vector<std::string> e172vp::BootstrapObject::sdlExtensions(SDL_Window *window) {
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

std::vector<char> e172vp::BootstrapObject::readFile(const std::string &filename) {
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

bool e172vp::BootstrapObject::isValid() const {
    return m_isValid;
}

e172vp::BootstrapObject::BootstrapObject(const std::string &assetFolder) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_window = SDL_CreateWindow("dfdf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_VULKAN);



    GraphicsObjectCreateInfo graphicsObjectCreateInfo;
    graphicsObjectCreateInfo.setRequiredExtensions(sdlExtensions(m_window));
    graphicsObjectCreateInfo.setApplicationName("test-app");
    graphicsObjectCreateInfo.setApplicationVersion(1);
    graphicsObjectCreateInfo.setDebugEnabled(true);
    graphicsObjectCreateInfo.setRequiredDeviceExtensions({ VK_KHR_SWAPCHAIN_EXTENSION_NAME });
    graphicsObjectCreateInfo.setSubpassCount(2);
    graphicsObjectCreateInfo.setSurfaceCreator([this](vk::Instance i, vk::SurfaceKHR *s) {
        VkSurfaceKHR ss;
        SDL_Vulkan_CreateSurface(m_window, i, &ss);
        *s = ss;
    });

    m_presentationObject = new PresentationObject(graphicsObjectCreateInfo);


    pipeline = m_presentationObject->createPipeline(
                0,
                PresentationObject::GlobalDSL | PresentationObject::SamplerDSL | PresentationObject::PerObjectDSL,
                readFile(e172::Additional::constrainPath(assetFolder + "/shaders/vert_uniform.spv")),
                readFile(e172::Additional::constrainPath(assetFolder + "/shaders/frag_sampler.spv")),
                vk::PrimitiveTopology::eTriangleList
                );


    pipeline2 = m_presentationObject->createPipeline(
                1,
                PresentationObject::GlobalDSL,
                readFile(e172::Additional::constrainPath(assetFolder + "/shaders/vert_linestrip.spv")),
                readFile(e172::Additional::constrainPath(assetFolder + "/shaders/frag_inter.spv")),
                vk::PrimitiveTopology::eLineStrip
                );


    font = new Font(
                m_presentationObject->graphicsObject()->logicalDevice(),
                m_presentationObject->graphicsObject()->physicalDevice(),
                m_presentationObject->graphicsObject()->commandPool(),
                m_presentationObject->graphicsObject()->graphicsQueue(),
                e172::Additional::constrainPath(assetFolder + "/fonts/ZCOOL.ttf"),
                128
                );

    m_presentationObject->setUiImage(font->character('a').image());
}

e172vp::BootstrapObject::~BootstrapObject() {
    delete m_presentationObject;
}
