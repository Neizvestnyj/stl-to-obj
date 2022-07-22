#ifndef TYPE_EXPORTOBJ_H_
#define TYPE_EXPORTOBJ_H_
#pragma once

#include <iostream>
#include <string>
#include "visitor.h"
#include "geometry.h"

class ExportOBJ : public Visitor<Geometry> {
    std::string filename_;
public:
    ExportOBJ(const std::string& filename) :
        filename_(filename) {}

    void dispatch(Geometry& model) override {
        std::cout << "Saving OBJ file: \"" << filename_ << "\"" << std::endl;
        save(model);
    }

    void save(Geometry& model);
};

#endif // TYPE_EXPORTOBJ_H_
