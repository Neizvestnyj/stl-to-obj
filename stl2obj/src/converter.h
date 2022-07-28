#pragma once

#include <string>

using namespace std;

void convert(string src, string dst, void(*callback)(int, void*), void* py_object);
