#ifndef TRAFFIC_PATH_H
#define TRAFFIC_PATH_H

#include "pool.h"

struct PathPiece {
    int id;
    int prev_road;
    int next_road;
};

class PathPool: public Pool<PathPiece> {
    public:
        PathPool(int size);
        void new_path_piece(int path_id, int prev_road, int next_road);
};

#endif
