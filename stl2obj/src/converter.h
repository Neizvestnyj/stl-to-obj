#pragma once

#include <string>

using namespace std;

void convert(string src, string dst, bool debug, void(*callback)(int, void*), void* py_callback, void* py_progress);
