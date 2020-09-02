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
        m_pointMesh = new e172vp::Mesh(e172vp::Mesh::plate(0.25));


    }
}

VulkanRenderer::~VulkanRenderer() {
    if(m_presentationObject)
        delete m_presentationObject;
}

bool VulkanRenderer::update() {
    if(m_presentationObject) {


        //GET OBJECTS FROM POOL
        std::map<e172vp::Mesh*, std::list<e172vp::VertexObject*>> usedObjects;
        for(auto reciept : m_reciepts) {
            auto& list = m_objectsPool[reciept.mesh];

            e172vp::VertexObject *obj;
            if(list.size() > 0) {
                obj = list.front();
                list.remove(obj);
            } else {
                obj = m_presentationObject->addVertexObject(*reciept.mesh);
                obj->setScale(glm::scale(glm::mat4(1.), glm::vec3(0.02)));
            }

            obj->setRotation(glm::rotate(glm::mat4(1.), reciept.rotation, glm::vec3(0., 0., 1.)));
            obj->setTranslation(glm::translate(glm::mat4(1.), glm::vec3(reciept.position.float32X(), reciept.position.float32Y(), 0)));
            obj->setVisible(true);
            usedObjects[reciept.mesh].push_back(obj);
        }

        //HIDE OBJECTS IN POOL
        for(auto l : m_objectsPool) {
            for(auto o : l.second)
                o->setVisible(false);
        }


        //PRESENT
        m_reciepts.clear();
        m_presentationObject->present();

        //RETURN OBJECTS TO POOL
        for(const auto& list : usedObjects) {
            for(auto object : list.second) {
                m_objectsPool[list.first].push_back(object);
            }
        }

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
    m_reciepts.push_back({ transformedPosition(point), 0, m_pointMesh });
    (void)point;
    (void)color;
}

void VulkanRenderer::drawLine(const e172::Vector &point0, const e172::Vector &point1, uint32_t color) {
    const auto tp0 = transformedPosition(point0);
    const auto tp1 = transformedPosition(point1);

    m_presentationObject->addVertexObject2({
                                               {  { tp0.float32X(), tp0.float32Y(), 0 }, { 0., 1., 0. }, {} },
                                               {  { tp1.float32X(), tp1.float32Y(), 0 }, { 0., 1., 0. }, {} }
                                           }, {
                                               0, 1
                                           });

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
    m_reciepts.push_back({ transformedPosition(position), static_cast<float>(angle), m_mesh0 });
    (void)image;
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
