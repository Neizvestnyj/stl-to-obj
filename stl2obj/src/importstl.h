#ifndef TYPE_IMPORTSTL_H_
#define TYPE_IMPORTSTL_H_
#pragma once

#include <string>
#include <iostream>
#include "visitor.h"
#include "geometry.h"

class ImportSTL : public Visitor<Geometry> {
    std::string filename_;
public:
    ImportSTL(const std::string& filename) : 
        filename_(filename) {}

    void dispatch(Geometry& model) override {
        std::cout << "Loading STL file \"" << filename_ << "\"" << std::endl;
        load(model);
    }
    
    void load(Geometry& model);
};

#endif // TYPE_IMPORTSTL_H_
