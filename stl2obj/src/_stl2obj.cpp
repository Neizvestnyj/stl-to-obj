#include <cstdio>
#include <cstdlib>


#include <string>
#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"
//#include "_stl2obj.h"
// // The name of this program
// static const char* PROGRAM_NAME = "stl2obj";

// // author
// static const char* AUTHOR = "Amir Baserinia/Neizvestnyj";

// version information
// void version()
// {
//     printf("%s converts an STL CAD file to OBJ format.\n", PROGRAM_NAME);
//     printf("Copyright (c) 2017-2022 %s\n", AUTHOR);
// }

//int convert(char* src, char* dst) {
int convert(std::string& src, std::string& dst) {
    /*
    src - full path to stl file
    dst - full path to obj file
    */

    // Variables that are set according to the specified options.
    bool merge_vertices = false;
    bool fill_holes = false;
    bool stich_curves = false;
    bool tolerance_val = false;

    //  create a geometry tesselation object
    Geometry tessel;

    //  fill up the tesselation object with STL data (load STL)
    tessel.visit(ImportSTL(src));

    //  write down the tesselation object into OBJ file (save OBJ)
    tessel.visit(ExportOBJ(dst));

    return 1;
}

/*
int main (int argc, char **argv)
{
    convert("F:\\VS\\stl-to-obj\\files\\surface.stl", "F:\\VS\\stl-to-obj\\files\\surface.obj");
    return EXIT_SUCCESS;
}
*/
