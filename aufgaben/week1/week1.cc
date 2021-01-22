#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#include "libweek1.h"

void print_help_message(char * argv[]) {
    cout << "Usage: " << argv[0] << " [-fgsa] FILENAME" << endl
         << endl
         << "   Analyse FILENAME. Note that this must be a csv file." << endl
         << endl
         << " -f\tGet line length." << endl
         << " -g\tGet average speed." << endl
         << " -s\tGet standard deviation." << endl
         << " -a\tGet all variables and store them in results.txt" << endl;
}

int main (int argc, char * argv[]) {
    enum {FILE_SIZE, AVG_SPEED, STD_SPEED, ALL} mode = ALL;

    /* Parse the command line arguments using getopt. More methods for argument
       parsing are available, most of which are better than this one. However
       getopt is exceedingly simple, which is why I chose it.
    */
    int opt;
    while ((opt = getopt(argc, argv, "fgsah")) != -1) {
        switch (opt) {
            case 'f': {
                mode = FILE_SIZE; break;
            }
            case 'g': {
                mode = AVG_SPEED; break;
            }
            case 's': {
                mode = STD_SPEED; break;
            }
            case 'a': {
                mode = ALL; break;
            }
            default:
            case 'h':
                print_help_message(argv);
                exit(EXIT_SUCCESS);
                break;
        }
    }

    string input_filename;
    // optind is an integer that indexes argv. After interpreting the flags it
    // points to the first argument after that. I require a file name from the
    // command line which is why I require one more option.
    if (optind >= argc) {
        print_help_message(argv);
        exit(EXIT_FAILURE);
    } else {
        input_filename = argv[optind];
    }

    int length = get_file_length(input_filename);

    if (mode == FILE_SIZE) {
        cout << length << endl;
        exit(EXIT_SUCCESS);
    }

    InputRow* rows = load_data_file(input_filename, length);
    Measurement* measurements = interprete_data(rows, length);
    delete [] rows;

    float* speeds = calculate_speeds(measurements, length);
    delete [] measurements;

    float average_speed = average(speeds, length);
    if (mode == AVG_SPEED) {
        cout << average_speed << endl;
        exit(EXIT_SUCCESS);
    }

    float std_speed = standard_deviation(speeds, length, average_speed);
    if (mode == STD_SPEED) {
        cout << std_speed << endl;
        exit(EXIT_SUCCESS);
    }

    if (mode == ALL) {
        cout << "Ran in ALL mode. Please consult 'results.txt' for the output." << endl;
        ofstream output_file("results.txt");
        output_file << "Input file: " << input_filename << endl
                    << "Number of rows: " << length << endl
                    << "Average speed: " << average_speed << endl
                    << "Standard deviation: " << std_speed << endl;
        output_file.close();
        exit(EXIT_SUCCESS);
    }

    return 0;
}
