#include "libweek1.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

/**
  Get the line amount of lines in a file.
  @param filename path to file
  @return line count
*/
int get_file_length(string filename) {
    ifstream input_file;
    input_file.open(filename, ios::in);

    string _;
    int c = 0;
    while (getline(input_file, _)) {c++;}
    input_file.close();
    return c;
}

/**
  Load csv file into rows.
  @param filename Filename of the file to be read.
  @param length Number of rows.
*/
InputRow* load_data_file(string filename, int length) {
    InputRow* rows = new InputRow[length];

    string row;
    ifstream input_file;
    input_file.open(filename, ios::in);
    int row_index = 0;
    while (getline(input_file, row)) {
        // Ensure no buffer overflow!
        if (row_index > length) {
            goto cleanup;
        }

        int column_index = 0;
        stringstream row_ss(row);
        string column;
        while (getline(row_ss, column, ',')) {
            float new_value = stof(column);
            switch (column_index) {
                case 0:
                    rows[row_index].start_time = new_value;
                    break;
                case 1:
                    rows[row_index].stop_time = new_value;
                    break;
                case 2:
                    rows[row_index].distance = new_value;
                    break;
            }
            column_index++;
        }
        row_index++;
    }
    // Undefined behaviour is bad behaviour! (Length could be shorter than file.)
    if (row_index != length) {
        goto cleanup;
    }
    input_file.close();

    return rows;

cleanup:
    delete rows;
    input_file.close();
    throw std::overflow_error("File length different than indicated.");
}

/**
  Interprete input into measurements.
  @param rows Rows that contain input.
  @param length Number of rows.
*/
Measurement* interprete_data(InputRow* rows, int length) {
    Measurement* measurements = new Measurement[length];
    for (int i=0;i<length;i++) {
        measurements[i].time = rows[i].stop_time - rows[i].start_time;
        measurements[i].distance = rows[i].distance;
    }
    return measurements;
}

/**
  Determine speed from measurements.
  @param measurements Measurents that need to be calculated from.
  @param length Number of measurements.
*/
float* calculate_speeds(Measurement* measurements, int length) {
    float* speeds = new float[length];
    for (int i=0;i<length;i++) {
        speeds[i] = measurements[i].distance / measurements[i].time;
    }
    return speeds;
}
