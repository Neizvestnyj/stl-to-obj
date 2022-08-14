#pragma once

#include <vector>

#include "StlTriangle.h"

using namespace std;

class StlModel
{
public:
    const vector<StlTriangle>& GetTriangles() const { return triangles_; }

    void AddTriangle(const StlTriangle& triangle);

private:
    vector<StlTriangle> triangles_;
};

