#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>

#include "importstl.h"
#include "vectornd.h"
#include "kdtree.h"
#include "progress.h"

template<typename T>
T read(ifstream& stream)
{
    char buffer[sizeof(T)];
    stream.read(buffer, sizeof(T));
    return *(T*)buffer;
}

// specialization
template<>
VectorND<> read<VectorND<>>(ifstream& stream)
{
    return VectorND<>(
        read<float>(stream),
        read<float>(stream),
        read<float>(stream)
    );
}

void ImportSTL::load(Geometry& model)
{
    int progress_val = 0;
    int progress_callback_counter = 1;
    // let's time the STL import
    auto t0 = chrono::high_resolution_clock::now();

    ifstream fileSTL (filename_.c_str(), ios::in | ios::binary);

    char header[80];
    fileSTL.read (header, 80);

    char numStr[4];
    fileSTL.read(numStr, 4);
    unsigned numOfTris = *(uint32_t*)numStr;
    cout << "Reading " << numOfTris << " triangles ..." << endl;

    // build search tree
    KDTree<3> tree;
    for (unsigned i = 0; i < numOfTris; i++) {
           // read the normal vector but ignore it.
        auto norm = read<VectorND<>>(fileSTL);
        float current = i;
        float total = numOfTris - 1;

        for (unsigned j = 0; j < 3; j++) {
            unsigned index;
            auto vec = read<VectorND<>>(fileSTL);
            int ind = tree.findNearest(vec);
            if ((ind < 0) || (VectorND<>::get_dist(vec, tree.getPoint(ind)) > 1.0e-8)) {
                index = tree.size();
                tree.insert(vec);
                model.verts_.push_back(vec);
            } else {
                index = ind;
            }
            model.faces_.push_back(index);
        }

        // skip 2 bytes of dummy data
        char dummy[2];
        fileSTL.read(dummy, 2);

        progress_val = lead_value(current, total);

        if (progress_val != -1)
        {

            if (callback_ && py_progress_) {
                if (progress_callback_counter == progress_part_){
                    callback_(1, py_progress_);
                    progress_callback_counter = 1;
                }
                else {
                    progress_callback_counter += 1;
                }
            }
            
            display_progress(progress_val, "Converting");
        }
            
    }
    cout << endl;

    // cout << "Points reduced from " << 3 * numOfTris << " to " << 
    //   tree.size() << " after merging!" << endl;

    chrono::duration<double> duration = 
        chrono::high_resolution_clock::now() - t0;
    cout << "Finished reading STL in " << (double)duration.count() <<
        " seconds!" << endl;
}

