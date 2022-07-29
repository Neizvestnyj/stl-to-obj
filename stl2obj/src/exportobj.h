#ifndef TYPE_EXPORTOBJ_H_
#define TYPE_EXPORTOBJ_H_
#pragma once

#include <iostream>
#include <string>
#include "visitor.h"
#include "geometry.h"

using namespace std;

class ExportOBJ : public Visitor<Geometry> {
    string filename_;
public:
    ExportOBJ(const string& filename) :
        filename_(filename) {}

    void dispatch(Geometry& model) override {
        cout << "Saving OBJ file: \"" << filename_ << "\"" << endl;
        save(model);
    }

    void save(Geometry& model);
};

#endif // TYPE_EXPORTOBJ_H_
