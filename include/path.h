#ifndef TRAFFIC_PATH_H
#define TRAFFIC_PATH_H

#include "pool.h"
#include <vector>

struct PathPiece {
    int id;
    int prev_road;
    int next_road;
};

class PathPool: public Pool<PathPiece> {
    private:
        int path_index;
    public:
        PathPool(int size);
        void new_path(std::vector<int> roads);
        void new_path_piece(int path_id, int prev_road, int next_road);
        int get_next_path_piece(int path, int current_road);
        int get_first_road(int path);
        std::vector<int> get_path(int id);
};

#endif
