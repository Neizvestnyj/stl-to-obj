#ifndef TYPE_GEOMETRY_H_
#define TYPE_GEOMETRY_H_
#pragma once

#include <vector>
#include "vectornd.h"
#include "geombase.h"
#include "visitor.h"

using namespace std;

// CRTP is used to avoid dynamic polymorphism
class Geometry : public GeomBase<Geometry> {
public:
    //  list of vertices as a vector of 3D points
    vector<VectorND<>> verts_;
    //  list of triangular faces as a vector of 3 indices. The indices point to
    //  the vertices in verts_.
    vector<unsigned> faces_;
public:
    Geometry() {}

    void visit(Visitor<Geometry>&& v) {
        v.dispatch(*this);
    }
};

#endif // TYPE_GEOMETRY_H_
