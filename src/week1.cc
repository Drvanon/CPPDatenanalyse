#include <iostream>
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
         << " -f\t Get line length." << endl
         << " -g\t Get average speed." << endl
         << " -s\t Get standard deviation." << endl;
}

int main (int argc, char * argv[]) {
    enum {FILE_SIZE, AVG_SPEED, STD_SPEED, ALL} mode = ALL;

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
            case 'h':
                print_help_message(argv);
        }
    }

    string input_filename;
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
    delete rows;

    return 0;
}
