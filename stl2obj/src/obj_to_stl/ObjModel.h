#pragma once

#include <vector>

#include "Coord3.h"
#include "FaceVertex.h"

using namespace std;

class ObjModel
{
public:
    const vector<Coord3>& GetVertices() const { return vertices_; }
    const vector<Coord3>& GetNorms() const { return norms_; }
    const vector<vector<FaceVertex>>& GetFaces() const { return faces_; }

    const Coord3& GetCoordMin() const { return coordMin_; }

    void AddVertex(const Coord3& v);
    void AddNorm(const Coord3& n);
    void AddFace(const vector<FaceVertex>& face);

    void(*callback_)(int, void*);
    void* py_progress_;

    ObjModel(void(*callback)(int, void*) = NULL, void* py_progress = NULL):
        py_progress_(py_progress),
        callback_(callback) {}

private:
    vector<Coord3> vertices_;
    vector<Coord3> norms_;
    vector<vector<FaceVertex>> faces_;

    Coord3 coordMin_;
};
