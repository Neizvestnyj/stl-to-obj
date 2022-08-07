#include <string>

#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"
#include "converter.h"
#include "mode.h"
#include "paths.h"

void convert(
    string src, 
    string dst, 
    bool debug = true,
    void(*callback)(int, void*) = NULL, 
    void* py_callback = NULL, 
    void* py_progress = NULL) {
    /*
    `src` - full path to stl file in binary format
    `dst` - full path to obj file
    `callback` - just function, that call pointer like `py_object`
    */

    int code = 0;
    int progress_part = 1; // how much progress must pass to trigger `py_progress(1)`
    string tmp_src = "";
    string mode = get_stl_mode(src);

    if (debug == false) {
        streambuf* old = cout.rdbuf();
        cout.rdbuf(0);
    }
    
    if (mode == "ASCII") {
        cout << "Convert ASCII to BIN" << endl;
        progress_part = 2;

        tmp_src = split_filename(src, "dir") + "tmp.stl";
        int res = stl_mode_converter(src, tmp_src, "ASCII", progress_part, callback, py_callback, py_progress);

        if (res != 0) {
            code = 1;
        }
        else {
            src = tmp_src;
        }
    }

    if (code == 0) {
        //  create a geometry tesselation object
        Geometry tessel;

        //  fill up the tesselation object with STL data (load STL)
        tessel.visit(ImportSTL(src, callback, py_progress, progress_part));

        //  write down the tesselation object into OBJ file (save OBJ)
        tessel.visit(ExportOBJ(dst));

        if (tmp_src != "") {
            remove(tmp_src.c_str());
            cout << tmp_src << " removed" << endl;
        }
    }

    if (callback && py_callback) {
        // for python lib `callback` written in c, `py_object` - pointer to python function
        callback(code, py_callback);
    }
}
