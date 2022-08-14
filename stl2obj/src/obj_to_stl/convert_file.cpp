#include "ObjReader.h"
#include "StlWriter.h"
#include "Converter.h"

#include <iostream>
#include <exception>
#include <sstream>
#include <vector>
#include <cstring>

void read_stl(ObjModel& model, const string& fname)
{
    ObjReader reader(model);
    reader.ReadFromFile(fname, model);

    cerr << "OBJ vertex count: " << model.GetVertices().size() << "\n";
    cerr << "OBJ normal count: " << model.GetNorms().size() << "\n";
    cerr << "OBJ face count: " << model.GetFaces().size() << "\n";
}

void write_obj(const StlModel& model, const string& fname)
{
    cerr << "STL triangle count: " << model.GetTriangles().size() << "\n";

    StlWriter writer(model);
    if (fname == "-")
        writer.WriteToStream(cout);
    else
        writer.WriteToFile(fname);
}

void convert_stl2obj(const ObjModel& modelIn, StlModel& modelOut, const Coord3TR& tr)
{
    Converter converter(tr);
    converter.Convert(modelIn, modelOut);
}
