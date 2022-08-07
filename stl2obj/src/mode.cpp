#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

#include "mode.h"
#include "progress.h"
#include "paths.h"

using namespace std;

string get_stl_mode(string file) {
    ifstream fin(file);

    char character;
    string solid;
    int count = 0;

    while (fin >> character) {
        if (count == 5) {
            break;
        }
        solid = solid + character;
        count++;
    }

    fin.close();

    if (solid == "solid") {
        return "ASCII";
    }
    else {
        return "BIN";
    }

}

int stl_mode_converter(string input_fname,
                       string output_fname,
                       string mode = "AUTO",
                       int progress_part = 1,
                       void(*callback)(int, void*) = NULL,
                       void* py_callback = NULL,
                       void* py_progress = NULL,
                       bool is_next = false
) {
    /*
    input_fname - path to stl input file
    output_fname - path to stl output file
    mode - if AUTO, programm automaticly detect stl mode ASCII or BIN
    */

    int retcode = 0; // 0 - all fine, 1 - error
    long file_line_number = 0;
    int progress_per_iteration = 0;
    int progress_val = 0;
    int progress_callback_counter = 1;

    ifstream input_stream;
    ofstream output_stream;
    string program_name;

    try {
        char buf[80];

        input_stream.open(input_fname, ios::in | ios::binary);
        if (!input_stream) {
            throw runtime_error("Error opening " + input_fname + " for reading");
        }
        if (!input_stream.read(buf, 5)) {
            throw runtime_error("Unable to determine input type: EOF reached");
        }
        input_stream.close();

        buf[5] = '\0';
        if (mode == "AUTO") {
            // check file type
            mode = get_stl_mode(input_fname);
        }

        if (mode == "ASCII") {
            // if file in ascii format
            input_stream.open(input_fname, ios::in);
            output_stream.open(output_fname, ios::out | ios::binary);
        }
        else {
            // if file in bin format
            input_stream.open(input_fname, ios::in | ios::binary);
            output_stream.open(output_fname, ios::out);
        }

        if (!input_stream) {
            throw runtime_error("Error opening " + input_fname + "for reading");
        }
        if (!output_stream) {
            throw runtime_error("Error opening " + output_fname + "for writing");
        }

        uint32_t facet_count = 0;
        if (mode == "ASCII") {  // ascii to binary
            file_line_number = calculate_line_numbers(input_fname) - 2;
            progress_per_iteration = file_line_number / 7;
            cout << file_line_number << " lines" << endl;

            runtime_error format_error("Invalid STL format");
            string token;

            input_stream >> token;

            if (token != "solid") throw format_error;

            getline(input_stream, token);
            token.erase(0, token.find_first_not_of(' '));
            if (token.size() > 80) throw format_error; // throw, if file have binary symbols and etc (\x00\x00)

            memset(buf, 0, 80);
            copy(token.begin(), token.end(), buf);
            output_stream.write(buf, 80);

            memset(buf, 0, 80);
            output_stream.write(buf, 4);

            while (input_stream >> token) {
                if (token == "facet") {
                    float vals[12];

                    input_stream >> token;
                    if (token != "normal") throw format_error;
                    for (int i = 0; i < 3; i++) {
                        input_stream >> vals[i];
                        if (!input_stream) throw format_error;
                    }

                    input_stream >> token;
                    if (token != "outer") throw format_error;
                    input_stream >> token;
                    if (token != "loop") throw format_error;

                    for (int i = 3; i < 12;) {
                        input_stream >> token;
                        if (token != "vertex") throw format_error;
                        for (int j = 0; j < 3; i++, j++) {
                            input_stream >> vals[i];
                            if (!input_stream) throw format_error;
                        }
                    }

                    input_stream >> token;
                    if (token != "endloop") throw format_error;
                    input_stream >> token;
                    if (token != "endfacet") throw format_error;

                    facet_count++;
                    output_stream.write(reinterpret_cast<char*>(vals), 48);
                    output_stream.write(buf, 2);

                    progress_val = lead_value((float)facet_count, (float)progress_per_iteration);

                    if (progress_val != -1)
                    {
                        if (progress_callback_counter == progress_part) {
                            callback(1, py_progress);
                            progress_callback_counter = 1;
                        }
                        else {
                            progress_callback_counter += 1;
                        }

                        display_progress(progress_val, "Convert ASCII to BIN");
                    }

                }
                else if (token == "endsolid") {
                    break;
                }
                else {
                    throw format_error;
                }
            }

            if (!input_stream) throw format_error;
            output_stream.seekp(80);
            output_stream.write(reinterpret_cast<char*>(&facet_count), 4);
            cout << endl;
            cout << "Succesfully converted " << facet_count << " polygons" << endl;
        }
        else {  // binary to ascii
            char title[81];
            input_stream.read(title, 80);
            title[80] = '\0';
            output_stream << "solid " << title << endl;

            input_stream.read(reinterpret_cast<char*>(&facet_count), 4);
            cout << "Faces " << facet_count << endl;

            for (uint32_t k = 0; k < facet_count; k++) {
                float vals[12];
                input_stream.read(reinterpret_cast<char*>(vals), 48);
                input_stream.ignore(2);

                output_stream << "  facet normal";
                for (int i = 0; i < 3; i++) {
                    output_stream << ' ' << vals[i];
                }
                output_stream << endl;
                output_stream << "    outer loop" << endl;
                for (int i = 3; i < 12; ) {
                    output_stream << "      vertex";
                    for (int j = 0; j < 3; i++, j++) {
                        output_stream << ' ' << vals[i];
                    }
                    output_stream << endl;
                }
                output_stream << "    endloop" << endl;
                output_stream << "  endfacet" << endl;

                progress_val = lead_value((float)k, (float)facet_count);

                if (progress_val != -1)
                {
                    if (progress_callback_counter == progress_part) {
                        callback(1, py_progress);
                        progress_callback_counter = 1;
                    }
                    else {
                        progress_callback_counter += 1;
                    }

                    display_progress(progress_val, "Convert BIN to ASCII");
                }

            }

            cout << endl;
            output_stream << "endsolid " << title << endl;
            cout << "Succesfully converted " << facet_count << " polygons" << endl;
        }
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        retcode = 1;
    }
    if (input_stream.is_open()) input_stream.close();
    if (output_stream.is_open()) output_stream.close();

    if (callback && py_callback && is_next == false) {
        callback(retcode, py_callback);
    }

    return retcode;
}
