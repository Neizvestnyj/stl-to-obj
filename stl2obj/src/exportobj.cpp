#include <fstream>
#include <chrono>

#include "exportobj.h"
#include "vectornd.h"

void ExportOBJ::save(Geometry& model)
{
    auto t0 = chrono::high_resolution_clock::now();

    ofstream fileOBJ (filename_.c_str(), ios::out);

    fileOBJ << "# Object name" << endl;
    fileOBJ << "o " << filename_ << endl;
    fileOBJ << endl;

    fileOBJ << "# Begin list of vertices" << endl;
    for (auto vec : model.verts_) {
        fileOBJ << "v " <<
            vec[0] << " " <<
            vec[1] << " " <<
            vec[2] << " 1.0" << endl;

    }
    fileOBJ << "# End list of vertices" << endl;
    fileOBJ << endl;

    fileOBJ << "# Begin list of faces" << endl;
    unsigned count = 0;
    for (auto ind : model.faces_) {
        if (count++ % 3 == 0) fileOBJ << "f ";
        fileOBJ << ind + 1 << " ";
        if (count % 3 == 0) fileOBJ << endl;
    }
    fileOBJ << "# End list of faces" << endl;
    fileOBJ << endl;

    chrono::duration<double> duration = 
        chrono::high_resolution_clock::now() - t0;
    cout << "Finished writing OBJ in " << (double)duration.count() <<
        " seconds!" << endl;
}

