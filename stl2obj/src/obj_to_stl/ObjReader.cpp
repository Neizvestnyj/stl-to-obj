#include "ObjReader.h"
#include "FaceVertex.h"
#include "../paths.h"
#include "../progress.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <stdexcept>

using namespace std;

void ObjReader::ReadFromFile(const string& fname, ObjModel& model)
{
    int num_lines = calculate_line_numbers(fname);

    ifstream file(fname);
    if (file.is_open())
    {
        ReadFromStream(file, num_lines, model);
        file.close();
        return;
    }
    throw runtime_error("Cannot open file: " + fname);
}

void ObjReader::ReadFromStream(istream& is, int num_lines, ObjModel& model)
{
    int line_counter = 0;
    int progress;

    string line;
    while (getline(is, line))
    {
        ParseLine(line);
        line_counter++;
        progress = lead_value(float(line_counter), float(num_lines));

        if (progress != -1) {
            if (model.callback_ && model.py_progress_) {
                model.callback_(1, model.py_progress_);
            }
            display_progress(progress, "Converting");
        }
    }

    cout << endl;
}

void ObjReader::ParseLine(const string& line)
{
    static const string rxCoordStr = "([-+]?[0-9]*.?[0-9]+(?:[eE][-+]?[0-9]+)?)";
    static const regex rxV = regex("^(?:\\s*)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:.*)");
    static const regex rxVT = regex("^(?:\\s*)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:.*)");
    static const regex rxVN = regex("^(?:\\s*)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:.*)");
    static const regex rxF = regex("(?:\\s*)((?:[-+]?[0-9]+)(?:/[-+]?[0-9]*)*)");  // 'v_ind' or 'v_ind/vt_ind' or 'v_ind/vt_ind/vn_ind' or 'v_ind//vn_ind'
    static const regex rxPrefix = regex("^(?:((?:\\s*)(f|v(?:n|t)?))\\s.*)"); // g1:prefix, g2:f|v|vn|vt
    
    smatch sm;
    if (regex_match(line, sm, rxPrefix))
    {
        if (sm[2].str() == "v" && regex_match(line.begin() + sm[1].length(), line.end(), sm, rxV))
        {
            AddVertex(stof(sm[1]), stof(sm[2]), stof(sm[3]));
        }
        else if (sm[2].str() == "vt" && regex_match(line.begin() + sm[1].length(), line.end(), sm, rxVT))
        {
            AddVertexTexture(stof(sm[1]), stof(sm[2]));
        }
        else if (sm[2].str() == "vn" && regex_match(line.begin() + sm[1].length(), line.end(), sm, rxVN))
        {
            AddVertexNorm(stof(sm[1]), stof(sm[2]), stof(sm[3]));
        }
        else if (sm[2].str() == "f")
        {
            vector<FaceVertex> faceVertices;

            string s(line.begin() + sm[1].length(), line.end());
            while (regex_search(s, sm, rxF))
            {
                FaceVertex faceVertex;
                int* vi = faceVertex.Indices(), * pvi = vi;

                istringstream tokenStream(sm[1].str());
                string token;
                while (getline(tokenStream, token, '/'))
                {
                    if (token.length() > 0)
                    {
                        *pvi = stoi(token);
                        if (*pvi < 0) // relative vertext indices
                        {
                            *pvi += static_cast<int>(pvi - vi == 0 ? model_.GetVertices().size() : pvi - vi == 2 ? model_.GetNorms().size() : 0) + 1;
                        }
                    }
                    if (++pvi - vi > 3) // check for overrun
                    {
                        cerr << "warn: face vertex contains more than 3 elements";
                        break;
                    }
                }

                faceVertices.push_back(faceVertex);
                s = sm.suffix().str();
            }

            AddFace(faceVertices);
        }
    }
}

void ObjReader::AddVertex(float x, float y, float z) const
{
    model_.AddVertex(Coord3(x, y, z));
}

void ObjReader::AddVertexNorm(float i, float j, float k)
{
   model_.AddNorm(Coord3(i, j, k));
}

void ObjReader::AddFace(const vector<FaceVertex>& faceVertexIndices)
{
    model_.AddFace(faceVertexIndices);
}

void ObjReader::AddVertexTexture(float u, float v)
{
    // TODO: not used
}
