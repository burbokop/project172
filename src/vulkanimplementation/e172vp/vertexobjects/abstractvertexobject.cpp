#include "abstractvertexobject.h"

bool e172vp::AbstractVertexObject::bindGlobalDescriptorSet() const { return m_bindGlobalDescriptorSet; }
void e172vp::AbstractVertexObject::setBindGlobalDescriptorSet(bool bindGlobalDescriptorSet) { m_bindGlobalDescriptorSet = bindGlobalDescriptorSet; }
e172vp::Pipeline *e172vp::AbstractVertexObject::pipeline() const { return m_pipeline; }
void e172vp::AbstractVertexObject::setPipeline(Pipeline *pipeline) { m_pipeline = pipeline; }
bool e172vp::AbstractVertexObject::visible() const { return m_visible; }
void e172vp::AbstractVertexObject::setVisible(bool visible) { m_visible = visible; }
e172vp::GraphicsObject *e172vp::AbstractVertexObject::graphicsObject() const { return m_graphicsObject; }

e172vp::AbstractVertexObject::AbstractVertexObject() {}
e172vp::AbstractVertexObject::~AbstractVertexObject() {}
