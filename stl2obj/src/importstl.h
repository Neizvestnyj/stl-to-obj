#ifndef TYPE_IMPORTSTL_H_
#define TYPE_IMPORTSTL_H_
#pragma once

#include <string>
#include <iostream>
#include "visitor.h"
#include "geometry.h"

using namespace std;

class ImportSTL: public Visitor<Geometry> {
    string filename_;
    int progress_part_;
    void(*callback_)(int, void*);
    void* py_progress_;

public:
    ImportSTL(const string& filename, 
        void(*callback)(int, void*) = NULL, 
        void* py_progress = NULL, 
        int progress_part = 1) :

        progress_part_(progress_part),
        filename_(filename),
        py_progress_(py_progress),
        callback_(callback) {}
 

    void dispatch(Geometry& model) override {
        cout << "Loading STL file \"" << filename_ << "\"" << endl;
        load(model);
    }
    
    void load(Geometry& model);
};

#endif // TYPE_IMPORTSTL_H_
