#include <string>
#include <fstream>

#include "check_mode.h"

using namespace std;

string get_stl_mode(string file) {
    int c;
    ifstream a(file);
    while ((c = a.get()) != EOF && c <= 127);

    if (c == EOF) {
        return "ASCII";
    }
    else {
        return "BIN";
    }

}
