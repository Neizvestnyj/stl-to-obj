#include <iostream>
#include <ctime>

#include "paths.h"

string split_filename(string str, string type = "dir")
{
    size_t found;

    found = str.find_last_of("/\\");
    if (type == "dir") {
        return str.substr(0, found + 1);
    }
    else {
        return str.substr(found + 1);
    }
}

unsigned int FileRead(istream& is, vector <char>& buff) {
    is.read(&buff[0], buff.size());
    return is.gcount();
}

int calculate_line_numbers(string file) {
    time_t now = time(0);
    const int SZ = 1024 * 1024;
    std::vector <char> buff(SZ);
    ifstream ifs(file);
    int n = 0;
    while (int cc = FileRead(ifs, buff)) {
        n += count(buff.begin(), buff.end(), '\n');
    }

    cout << "Calculating takes: " << time(0) - now << endl;

    return n;
}
