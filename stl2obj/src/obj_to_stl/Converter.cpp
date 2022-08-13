#include "Converter.h"

#include <stdexcept>
#include <algorithm>
#include <cfloat>

using namespace std;

void Converter::Convert(const ObjModel& objModel, StlModel& stlModel)
{
    // collect coordinates for polygon faces
    for (const auto& f : objModel.GetFaces())
    {
        CreatePolygonsWithNorms(f, objModel.GetVertices(), objModel.GetNorms());
    }

    // convert polygons to triangles
    for (const auto& poly : polygons_)
    {
        Coord3 translate = trMatix_.ApplyTransformation(objModel.GetCoordMin());
        CreateTrianglesWithNormsAndTransform(poly, translate);
    }

    // sort triangles by z axis (not strictly enforced)
    sort(triangles_.begin(), triangles_.end(),
        [](const array<Coord3, 3>& a, const array<Coord3, 3>& b) -> bool
        {
            return min({ a[0].z, a[1].z, a[2].z }) > min({ b[0].z, b[1].z, b[2].z });
        });

    // move triangles to stl
    for (const auto& t : triangles_)
    {
        // generate normal which should be perpendicular to the triangle plane
        Coord3 nv = Coord3::CrossProduct(t[1] - t[0], t[2] - t[0]).Normalize();

        stlModel.AddTriangle({ t[0], t[1], t[2], nv });
    }
}

void Converter::CreatePolygonsWithNorms(const vector<FaceVertex>& faceVertices, const vector<Coord3>& objVertices, const vector<Coord3>& objNorms)
{
    // collect face vertices with norms
    vector<Coord3N> face;
    for (auto const& v : faceVertices)
    {
        const Coord3& vt = v.vIndex() ? objVertices[static_cast<size_t>(v.vIndex() - 1)] : Coord3();
        const Coord3& vn = v.vnIndex() ? objNorms[static_cast<size_t>(v.vnIndex() - 1)] : Coord3();

        face.push_back({ vt, vn });
    }
    polygons_.push_back(face);
}

void Converter::CreateTrianglesWithNormsAndTransform(const vector<Coord3N>& poly, const Coord3& translate)
{
    if (poly.size() < 3)
    {
        throw runtime_error("Polygon has less than 3 vertices");
    };   

    // traverse polygon and make triangles
    for (vector<Coord3N>::const_iterator it = poly.begin(); it+2 != poly.end(); ++it)
    {
        const Coord3N& p0 = *poly.begin();
        const Coord3N& p1 = *(it+1);
        const Coord3N& p2 = *(it+2);

        array<Coord3, 3> triangle
        { 
            trMatix_.ApplyTransformation(p0.vt - translate),
            trMatix_.ApplyTransformation(p1.vt - translate),
            trMatix_.ApplyTransformation(p2.vt - translate)
        };

        triangles_.push_back(triangle);
    }
}
