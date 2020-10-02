#include "colider.h"
#include "math.h"
#include <list>
#include <src/engine/utility/vectorproxy.h>

std::vector<e172::Colider::PositionalVector> e172::Colider::edges() const {
    return m_edges;
}

void e172::Colider::setMatrix(const Matrix &matrix) {
    m_matrix = matrix;
}

void e172::Colider::setPosition(const Vector &position) {
    m_position = position;
}

size_t e172::Colider::collisionCount() const {
    return m_collisionCount;
}

size_t e172::Colider::significantNormalCount() const {
    return m_significantNormalCount;
}

std::vector<e172::Colider::PositionalVector> e172::Colider::escapeVectors() const {
    return m_escapeVectors;
}

e172::Vector e172::Colider::collisionPoint() const {
    return m_collisionPoint;
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

e172::Vector e172::Colider::perpendecularProjection(const e172::Vector &p0, const e172::Vector &p1, const e172::Vector &v) {
    return (p1 - p0).projection(v.leftNormal());
}

bool e172::Colider::penetration(double x0, double w0, double x1, double w1) {
//    return ((x0 < x1) && (x1 < (x0 + w0)))
//            || ((x0 < (x1 + w1)) && ((x1 + w1) < (x0 + w0)))
//            || ((x1 < x0) && (x0 < (x1 + w1)))
//            || ((x1 < (x0 + w0)) && ((x0 + w0) < (x1 + w1)));

    return (x1 - x0) * (x1 - x0 - w0) < 0
            || (x1 + w1 - x0) * (x1 + w1 - x0 - w0) < 0
            || (x0 - x1) * (x0 - x1 - w1) < 0
            || (x0 + w0 - x1) * (x0 + w0 - x1 - w1) < 0;
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

std::pair<e172::Colider::PositionalVector, e172::Colider::PositionalVector> e172::Colider::narrowCollision(e172::Colider *c0, Colider *c1) {
    auto e0 = transformed(c0->m_edges, c0->m_matrix);
    auto e1 = transformed(c1->m_edges, c1->m_matrix);
    VectorProxy<PositionalVector> edgesProxy({ &e0, &e1 });

    c0->m_projections.resize(edgesProxy.size());
    c1->m_projections.resize(edgesProxy.size());

    size_t coll_count = 0;
    size_t fv_count = 0;

    if(c0->m_escapeVectors.size() != edgesProxy.size())
        c0->m_escapeVectors.resize(edgesProxy.size());
    if(c1->m_escapeVectors.size() != edgesProxy.size())
        c1->m_escapeVectors.resize(edgesProxy.size());

    std::list<PositionalVector> ev;

    e172::Vector averagePosition;
    for(size_t i = 0, count = edgesProxy.size(); i < count; ++i) {
        const auto normal = edgesProxy[i].leftNormal();
        c0->m_projections[i] = objectProjection(e0, normal);
        c1->m_projections[i] = objectProjection(e1, normal);

        c0->m_projections[i].position += c0->m_position;
        c1->m_projections[i].position += c1->m_position;

        c1->m_projections[i].position += perpendecularProjection(c1->m_projections[i].position, c0->m_projections[i].position, c0->m_projections[i].vector);

        if(c0->m_projections[i].vector.cheapModule() && c1->m_projections[i].vector.cheapModule()) {
            ++fv_count;
        }


        if(penetration(c0->m_projections[i].position.x(), c0->m_projections[i].vector.x(), c1->m_projections[i].position.x(), c1->m_projections[i].vector.x())) {
            c0->m_projections[i].colided = true;
            c1->m_projections[i].colided = true;
            coll_count++;

            if(c0->m_projections[i].position.x() < c1->m_projections[i].position.x()) {
                c0->m_escapeVectors[i] = { (c1->m_projections[i].position + c1->m_projections[i].vector + c0->m_projections[i].position) / 2, (c0->m_projections[i].vector - c1->m_projections[i].position + c0->m_projections[i].position) };
                c0->m_escapeVectors[i].vector = -c0->m_escapeVectors[i].vector;
            } else {
                c0->m_escapeVectors[i] = { (c1->m_projections[i].position + c1->m_projections[i].vector + c0->m_projections[i].position) / 2, (c1->m_projections[i].vector - c0->m_projections[i].position + c1->m_projections[i].position) };
            }
            c1->m_escapeVectors[i] = { c0->m_escapeVectors[i].position, -c0->m_escapeVectors[i].vector };

            c0->m_escapeVectors[i].vector /= 2;
            c1->m_escapeVectors[i].vector /= 2;

            ev.push_back(c0->m_escapeVectors[i]);
        } else {
            c0->m_escapeVectors[i] = {};
            c1->m_escapeVectors[i] = {};
        }


        averagePosition += c0->m_projections[i].position;
        averagePosition += c1->m_projections[i].position;
    }
    c0->m_collisionCount = coll_count;
    c1->m_collisionCount = coll_count;
    c0->m_significantNormalCount = fv_count;
    c1->m_significantNormalCount = fv_count;

    if(coll_count >= fv_count) {
        const auto it = std::min_element(ev.begin(), ev.end(), &PositionalVector::moduleLessComparator);
        if(it != ev.end()) {

            if(ev.begin() != ev.end()) {
                it->position = PositionalVector::linesIntersection(ev.front().leftNormal().line(), ev.back().leftNormal().line());
            }

            return { *it, -*it };
        }
        return {};
    }
    return {};
}

e172::Colider::PositionalVector e172::Colider::PositionalVector::leftNormal() const {
    return { position, vector.leftNormal() };
}

e172::Colider::PositionalVector e172::Colider::PositionalVector::rightNormal() const {
    return { position, vector.rightNormal() };
}

e172::Colider::PositionalVector e172::Colider::PositionalVector::operator-() const {
    return { position, -vector };
}

bool e172::Colider::PositionalVector::moduleLessComparator(const e172::Colider::PositionalVector &v0, const e172::Colider::PositionalVector &v1) {
    return v0.vector.module() < v1.vector.module();
}

e172::Vector e172::Colider::PositionalVector::line() const {
    if(vector.x() != e172::Math::null) {
        const auto k = vector.y() / vector.x();
        return { k, position.y() - k * position.x() };
    }
    return { std::numeric_limits<double>::max(), position.x() };
}

e172::Vector e172::Colider::PositionalVector::linesIntersection(const e172::Vector &line0, const e172::Vector &line1) {
    const double kk = line1.x() - line0.x();
    if(kk != e172::Math::null) {
        const auto x = (line0.y() - line1.y()) / kk;
        const auto y = line0.x() * x + line0.y();
        return { x, y };
    }
    return { 0, 0 };
}
