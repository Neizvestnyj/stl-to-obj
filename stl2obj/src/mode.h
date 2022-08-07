#pragma once

#include <string>

using namespace std;
int stl_mode_converter(string input_fname, 
					   string output_fname, 
					   string mode,
					   int progress_part,
					   void(*callback)(int, void*),
					   void* py_callback,
					   void* py_progress,
					   bool is_next
	);
string get_stl_mode(string file);
