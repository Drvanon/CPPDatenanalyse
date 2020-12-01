#ifndef ENTITIES_H
#define ENTITIES_H
struct Road {
    int id;
    float start_x;
    float start_y;
    float stop_x;
    float stop_y;
};

struct Car {
    int id;
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    float acc_x;
    float acc_y;
    int road;
    int path;
};

struct Path {
    int id;
    int prev_road;
    int next_road;
};

#endif
