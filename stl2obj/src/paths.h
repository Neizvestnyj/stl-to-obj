#include <string>
#include <vector>
#include <fstream>

using namespace std;

string split_filename(string str, string type);
string get_extention(string filename);
unsigned int FileRead(istream& is, vector <char>& buff);
int calculate_line_numbers(string file);
