#include "vulkanrenderer.h"

#include "e172vp/presentationobject.h"

#include "../engine/additional.h"

#include "e172vp/tools/mesh.h"
#include <glm/gtc/matrix_transform.hpp>

VulkanRenderer::VulkanRenderer(const std::vector<std::string> &args) {
    if(args.size() > 0) {
        const auto assetFolder = e172::Additional::absolutePath("../assets", args[0]);
        m_presentationObject = new e172vp::PresentationObject(assetFolder);
        m_mesh0 = new e172vp::Mesh(e172vp::Mesh::load(e172::Additional::constrainPath(assetFolder + "/meshes/ship1.obj")));
        m_mesh1 = new e172vp::Mesh(e172vp::Mesh::load(e172::Additional::constrainPath(assetFolder + "/meshes/ship2.obj")));
    }
}

VulkanRenderer::~VulkanRenderer() {
    if(m_presentationObject)
        delete m_presentationObject;
}

bool VulkanRenderer::update() {
    if(m_presentationObject) {
        while(m_reciepts.size() > m_objectsPool.size()) {
            auto obj = m_presentationObject->addVertexObject(*m_mesh0);
            obj->setScale(glm::scale(glm::mat4(1.), glm::vec3(0.02)));
            m_objectsPool.push_back(obj);
        }
        for(auto p : m_objectsPool) {
            p->setVisible(false);
        }

        auto obj_it = m_objectsPool.begin();
        for(auto rec_it = m_reciepts.begin(); rec_it != m_reciepts.end(); ++rec_it) {
            (*obj_it)->setRotation(glm::rotate(glm::mat4(1.), rec_it->rotation, glm::vec3(0., 0., 1.)));
            (*obj_it)->setTranslation(glm::translate(glm::mat4(1.), glm::vec3(rec_it->position.float32X(), rec_it->position.float32Y(), 0)));
            (*obj_it)->setVisible(true);
            ++obj_it;
        }


        m_reciepts.clear();
        m_presentationObject->present();
        return true;
    }
    return false;
}

bool VulkanRenderer::isValid() const {
    if(m_presentationObject)
        return m_presentationObject->isValid();

    return false;
}

void VulkanRenderer::fill(uint32_t color) {
    (void)color;
}

void VulkanRenderer::drawPixel(const e172::Vector &point, uint32_t color) {
    (void)point;
    (void)color;
}

void VulkanRenderer::drawLine(const e172::Vector &point0, const e172::Vector &point1, uint32_t color) {
    (void)point0;
    (void)point1;
    (void)color;
}

void VulkanRenderer::drawRect(const e172::Vector &point0, const e172::Vector &point1, uint32_t color) {
    (void)point0;
    (void)point1;
    (void)color;
}

void VulkanRenderer::drawSquare(const e172::Vector &point, int radius, uint32_t color) {
    (void)point;
    (void)radius;
    (void)color;
}

void VulkanRenderer::drawCircle(const e172::Vector &point, int radius, uint32_t color) {
    (void)point;
    (void)radius;
    (void)color;
}

void VulkanRenderer::drawDiagonalGrid(const e172::Vector &point0, const e172::Vector &point1, int interval, uint32_t color) {
    (void)point0;
    (void)point1;
    (void)interval;
    (void)color;
}

void VulkanRenderer::drawImage(const e172::Image &image, const e172::Vector &position, double angle, double zoom) {
    m_reciepts.push_back({ (position - m_resolution / 2) / 1080, static_cast<float>(angle) });
    (void)image;
    (void)position;
    (void)angle;
    (void)zoom;
}

e172::Vector VulkanRenderer::drawString(const std::string &string, const e172::Vector &positions, uint32_t color, const e172::TextFormat &format) {
    (void)string;
    (void)positions;
    (void)color;
    (void)format;
    return e172::Vector();
}

void VulkanRenderer::applyLensEffect(const e172::Vector &point0, const e172::Vector &point1, double coefficient) {
    (void)point0;
    (void)point1;
    (void)coefficient;
}

void VulkanRenderer::applySmooth(const e172::Vector &point0, const e172::Vector &point1, double coefficient) {
    (void)point0;
    (void)point1;
    (void)coefficient;
}

void VulkanRenderer::enableEffect(uint64_t effect) {
    (void)effect;
}

void VulkanRenderer::disableEffect(uint64_t effect) {
    (void)effect;
}

void VulkanRenderer::setFullscreen(bool value) {
    (void)value;
}

void VulkanRenderer::setResolution(e172::Vector value) {
    (void)value;
}

e172::Vector VulkanRenderer::resolution() const {
    return m_resolution;
}

e172::Vector VulkanRenderer::screenSize() const {
    return m_resolution;
}
