#include "colider.h"


std::vector<e172::Colider::PositionalVector> e172::Colider::edges() const {
    return m_edges;
}

void e172::Colider::setMatrix(const Matrix &matrix) {
    m_matrix = matrix;
}

std::vector<e172::Colider::PositionalVector> e172::Colider::makeEdges(const std::vector<e172::Vector> &vertices) {
    std::vector<PositionalVector> edges(vertices.size());
    for(size_t i = 0; i < vertices.size(); ++i) {
        if(i < vertices.size() - 1) {
            edges[i] = { vertices[i], vertices[i + 1] - vertices[i] };
        } else {
            edges[i] = { vertices[i], vertices[0] - vertices[i] };
        }
    }
    return edges;
}

std::vector<e172::Colider::PositionalVector> e172::Colider::transformed(const std::vector<e172::Colider::PositionalVector> &vector, const e172::Matrix &matrix) {
    std::vector<e172::Colider::PositionalVector> result(vector.size());
    for(size_t i = 0, count = vector.size(); i < count; ++i) {
        result[i].position = matrix * vector[i].position;
        result[i].vector = matrix * vector[i].vector;
    }
    return result;
}

e172::Colider::Colider() {}

std::vector<e172::Vector> e172::Colider::vertices() const {
    return m_vertices;
}

void e172::Colider::setVertices(const std::vector<Vector> &vertices) {
    m_vertices = vertices;
    m_edges = makeEdges(vertices);
    m_projections.resize(vertices.size());
    for(size_t i = 0; i < m_edges.size(); ++i) {
        m_projections[i] = objectProjection(m_edges, m_edges[i].leftNormal());
    }
}

std::vector<e172::Colider::PositionalVector> e172::Colider::projections() const {
    return m_projections;
}

void e172::Colider::narrowCollision(e172::Colider *colider) {
    auto e0 = transformed(m_edges, m_matrix);
    auto e1 = transformed(colider->m_edges, colider->m_matrix);
    VectorProxy<PositionalVector> edgesProxy({ &e0, &e1 });

    m_projections.resize(edgesProxy.size());
    colider->m_projections.resize(edgesProxy.size());
    for(size_t i = 0, count = edgesProxy.size(); i < count; ++i) {
        m_projections[i] = objectProjection(e0, edgesProxy[i].leftNormal());
        colider->m_projections[i] = objectProjection(e1, edgesProxy[i].leftNormal());;
    }
}

e172::Colider::PositionalVector e172::Colider::PositionalVector::leftNormal() const {
    return { position, vector.leftNormal() };
}

e172::Colider::PositionalVector e172::Colider::PositionalVector::rightNormal() const {
    return { position, vector.rightNormal() };
}
