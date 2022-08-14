#pragma once

#include "ObjModel.h"
#include "StlModel.h"

#include <vector>
#include <array>

using namespace std;

class Converter
{
public:
    Converter(Coord3TR trMatix) : trMatix_(trMatix) {}
    void Convert(const ObjModel& objModel, StlModel& stlModel);

private:
    vector<vector<Coord3N>> polygons_;    // list of faces -> list of coordinate pairs (vertex, norm)
    vector<array<Coord3,3>> triangles_;  // list of faces -> 3 * coordinates

    Coord3TR trMatix_;

    void CreatePolygonsWithNorms(const vector<FaceVertex>& faceVertices, const vector<Coord3>& objVertices, const vector<Coord3>& objNorms);
    void CreateTrianglesWithNormsAndTransform(const vector<Coord3N>& poly, const Coord3& translate);
};



