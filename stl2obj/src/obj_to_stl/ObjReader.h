#pragma once

#include "ObjModel.h"

#include <string>
#include <vector>
#include <istream>

using namespace std;

class ObjReader
{
public:
    ObjReader(ObjModel& model) : model_(model) {}

    void ReadFromFile(const string& fname, ObjModel& model);
    void ReadFromStream(istream& is, int num_lines, ObjModel& model);

    ObjModel& model_;

    void ParseLine(const string& line);

private:
    void AddVertex(float x, float y, float z) const;
    void AddVertexTexture(float u, float v);
    void AddVertexNorm(float i, float j, float k);
    void AddFace(const vector<FaceVertex>& faceVertexIndices);
};


