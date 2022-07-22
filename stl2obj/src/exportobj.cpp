#include <fstream>
#include <chrono>
#include "exportobj.h"
#include "vectornd.h"


void ExportOBJ::save(Geometry& model)
{
    auto t0 = std::chrono::high_resolution_clock::now();

    std::ofstream fileOBJ (filename_.c_str(), std::ios::out);

    fileOBJ << "# Object name" << std::endl;
    fileOBJ << "o " << filename_ << std::endl;
    fileOBJ << std::endl;

    fileOBJ << "# Begin list of vertices" << std::endl;
    for (auto vec : model.verts_) {
        fileOBJ << "v " <<
            vec[0] << " " <<
            vec[1] << " " <<
            vec[2] << " 1.0" << std::endl;

    }
    fileOBJ << "# End list of vertices" << std::endl;
    fileOBJ << std::endl;

    fileOBJ << "# Begin list of faces" << std::endl;
    unsigned count = 0;
    for (auto ind : model.faces_) {
        if (count++ % 3 == 0) fileOBJ << "f ";
        fileOBJ << ind + 1 << " ";
        if (count % 3 == 0) fileOBJ << std::endl;
    }
    fileOBJ << "# End list of faces" << std::endl;
    fileOBJ << std::endl;

    std::chrono::duration<double> duration = 
        std::chrono::high_resolution_clock::now() - t0;
    std::cout << "Finished writing OBJ in " << (double)duration.count() <<
        " seconds!" << std::endl;
}

