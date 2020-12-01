#include "path.h"

PathPool::PathPool(int size): Pool<PathPiece>(size) {
    this->path_index = 0;
    this->path_piece_index = 0;
}

void PathPool::new_path(std::vector<int> roads) {
    for (int i=0;i < roads.size() - 1; i++) {
        this->new_path_piece(this->path_index, roads[i], roads[i+1]);
    }
    this->path_index++;
}

void PathPool::new_path_piece(int path_id, int prev_road, int next_road) {
    PathPiece path_piece;
    path_piece.id = path_id;
    path_piece.prev_road = prev_road;
    path_piece.next_road = next_road;
    this->pool[this->path_piece_index] = path_piece;
    this->path_piece_index++;
}

int PathPool::get_next_path_piece(int path, int current_road) {
    for (int i=0;i < this->size;i++) {
        PathPiece path_piece = this->pool[i];
        if (path_piece.id == path && path_piece.prev_road == current_road){
            return path_piece.next_road;
        }
    }
    return -1;
}

int PathPool::get_first_road(int path) {
    for (int i=0;i < this->size;i++) {
        PathPiece path_piece = this->pool[i];
        if (path_piece.id == path) {
            return path_piece.prev_road;
        }
    }
    return -1;
}
