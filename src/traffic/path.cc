#include "path.h"

PathPool::PathPool(int size): Pool<PathPiece>(size) {
    this->path_index = 0;
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
    this->pool[this->index] = path_piece;
    this->index++;
}

int PathPool::get_next_path_piece(int path, int current_road) {
    for (int i=0; i<this->index; i++) {
        PathPiece path_piece = (*this)[i];
        if (path_piece.id == path && path_piece.prev_road == current_road){
            return path_piece.next_road;
        }
    }
    return -1;
}

std::vector<int> PathPool::get_path(int id) {
    int cur_road = this->get_first_road(id);
    std::vector path = {cur_road};
    while (cur_road = this->get_next_path_piece(id, cur_road) != -1)
        path.push_back(cur_road);

        return path;
}

int PathPool::get_first_road(int path) {
    for (int i=0;i < this->index; i++) {
        PathPiece path_piece = (*this)[i];
        if (path_piece.id == path) {
            return path_piece.prev_road;
        }
    }
    return -1;
}
