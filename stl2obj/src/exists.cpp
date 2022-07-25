#include <string>
#include <fstream>
#include "exists.h"

using namespace std;

bool is_file_exist(string file)
{
    ifstream infile(file);
    return infile.good();
}
