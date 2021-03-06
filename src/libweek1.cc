#include "libweek1.h"

#include <iostream>
#include <cmath>
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
    ifstream input_file(filename, ios::in);

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
    ifstream input_file(filename, ios::in);
    int row_index = 0;
    while (
            input_file >> rows[row_index].start_time
                       >> rows[row_index].stop_time
                       >> rows[row_index].distance
    ) {
        // Ensure no buffer overflow!
        if (row_index > length) {
            goto cleanup;
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

/**
  Calculate the average of an array.
  @param values Values that will be averaged.
  @param length Number of values.
*/
float average(float* values, int length) {
    float sum = 0;
    for (int i=0;i<length;i++) {
        sum += values[i];
    }
    return sum / length;
}

/**
  Calculate the standard deviation of an array.
  @param values Values of which the std will be found.
  @param length Number of values.
*/
float standard_deviation(float* values, int length) {
    float mean = average(values, length);

    return standard_deviation(values, length, mean);
}

/**
  Calculate the standard deviation of an array, without recalculating the average.
  @param values Values of which the std will be found.
  @param length Number of values.
  @param average Average to assume.
*/
float standard_deviation(float* values, int length, float average) {
    float var = 0;
    for (int i=0;i<length;i++) {
        var += pow(values[i] - average, 2);
    }
    return sqrt(var/length);
}
