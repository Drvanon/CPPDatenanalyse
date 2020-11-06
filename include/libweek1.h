#ifndef LIBWEEK_H
#define LIBWEEK_H

#include <string>
using namespace std;

struct InputRow {
    float start_time;
    float stop_time;
    float distance;
};

struct Measurement {
    float time;
    float distance;
};


int get_file_length(string filename);
InputRow* load_data_file(string filename, int length);
Measurement* interprete_data(InputRow* rows, int length);
float* calculate_speeds(Measurement* measurements, int length);
float average(float* values, int length);
float standard_deviation(float* values, int length);
float standard_deviation(float* values, int length, float average);

#endif
