#include <cstdio>
#include <cstdlib>
#include <string>

#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"
#include "_stl2obj.h"

namespace std {

    int convert(string src, string dst) {
        /*
        src - full path to stl file
        dst - full path to obj file
        return 0
        */

        //  create a geometry tesselation object
        Geometry tessel;

        //  fill up the tesselation object with STL data (load STL)
        tessel.visit(ImportSTL(src));

        //  write down the tesselation object into OBJ file (save OBJ)
        tessel.visit(ExportOBJ(dst));

        return 0;
    }
}

/*
int main (int argc, char **argv)
{
    std::convert("F:\\VS\\stl-to-obj\\files\\surface.stl", "F:\\VS\\stl-to-obj\\files\\surface.obj");
    return EXIT_SUCCESS;
}
*/