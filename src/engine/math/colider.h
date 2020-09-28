#ifndef COLIDER_H
#define COLIDER_H

#include "matrix.h"
#include "vector.h"
#include <vector>

#include <algorithm>


namespace e172 {


template<typename T>
class VectorProxy {
    std::vector<std::vector<T>*> m_pointers;
public:
    VectorProxy(const std::vector<std::vector<T>*> &pointers) {
        m_pointers = pointers;
    }

    size_t size() const {
        size_t sum = 0;
        for(auto p : m_pointers) {
            sum += p->size();
        }
        return sum;
    }

    T &operator[](size_t index) {
        size_t pi = 0;
        while(index >= m_pointers[pi]->size()) {
            index -= m_pointers[pi]->size();
            ++pi;
        }
        return (*m_pointers[pi])[index];
    }

    T operator[](size_t index) const {
        size_t pi = 0;
        while(index >= m_pointers[pi]->size()) {
            index -= m_pointers[pi]->size();
            ++pi;
        }
        return (*m_pointers[pi])[index];
    }

};



class Colider {
public:
    struct PositionalVector {
        Vector position;
        Vector vector;
        bool colided = false;
        PositionalVector leftNormal() const;
        PositionalVector rightNormal() const;
    };
private:

    std::vector<Vector> m_vertices;
    std::vector<PositionalVector> m_edges;
    std::vector<PositionalVector> m_projections;
    Matrix m_matrix;
    Vector m_position;

public:
    template<typename T>
    static PositionalVector objectProjection(const T &edges, const PositionalVector& vector) {
        std::vector<e172::Vector> tmp_proj(edges.size() * 2);
        for(size_t e = 0, count = edges.size(); e < count; ++e) {
            //tmp_proj[e * 2] = (edges[e].position - vector.position).projection(vector.vector);
            tmp_proj[e * 2] = edges[e].position.projection(vector.vector);
            tmp_proj[e * 2 + 1] = tmp_proj[e * 2] + edges[e].vector.projection(vector.vector);
        }

        const auto it0 = std::min_element(tmp_proj.begin(), tmp_proj.end(), [](const e172::Vector &v0, const e172::Vector &v1) {
            return v0.x() < v1.x();
        });
        const auto it1 = std::max_element(tmp_proj.begin(), tmp_proj.end(), [](const e172::Vector &v0, const e172::Vector &v1) {
            return v0.x() < v1.x();
        });
        if(it0 != tmp_proj.end() && it1 != tmp_proj.end()) {
            if(vector.vector.x() < 0) {
                return { *it0, (*it1 - *it0) };
            } else {
                return { *it1, (*it0 - *it1) };
            }
        }
        return {};
    }
    static std::vector<PositionalVector> makeEdges(const std::vector<Vector> &vertices);
    static std::vector<PositionalVector> transformed(const std::vector<PositionalVector> &vector, const e172::Matrix &matrix);
    static Vector perpendecularProjection(const e172::Vector &p0, const e172::Vector &p1, const Vector &v);
    static bool penetration(double x0, double w0, double x1, double w1);

    Colider();
    std::vector<Vector> vertices() const;
    void setVertices(const std::vector<Vector> &vertices);
    std::vector<PositionalVector> projections() const;

    static std::pair<Vector, Vector> narrowCollision(Colider *c0, Colider *c1);

    std::vector<PositionalVector> edges() const;
    void setMatrix(const Matrix &matrix);
    void setPosition(const Vector &position);
};

}
#endif // COLIDER_H
