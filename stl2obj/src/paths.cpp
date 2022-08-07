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

template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
base_count(InputIterator first, InputIterator last, const T& val)
{
    typename iterator_traits<InputIterator>::difference_type ret = 0;
    while (first != last) {
        if (*first == val) ++ret;
        ++first;
    }
    return ret;
}

int calculate_line_numbers(string file) {
    time_t now = time(0);
    const int SZ = 1024 * 1024;
    std::vector <char> buff(SZ);
    ifstream ifs(file);
    int n = 0;
    while (FileRead(ifs, buff)) {
        n += base_count(buff.begin(), buff.end(), '\n');
    }

    cout << "Calculating takes: " << time(0) - now << endl;

    return n;
}
