#include "ObjReader.h"
#include "StlWriter.h"

using namespace std;

void read_stl(ObjModel& model, const string& fname);

void write_obj(const StlModel& model, const string& fname);

void convert_stl2obj(const ObjModel& modelIn, StlModel& modelOut, const Coord3TR& tr);
