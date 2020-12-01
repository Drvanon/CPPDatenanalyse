#include "path.h"

PathPool::PathPool(int size): Pool<PathPiece>(size) {}

void new_path_piece(int path_id, int prev_road, int next_road) {
    PathPiece path_piece;
    path_piece.id = path_id;
    path_piece.prev_road = prev_road;
    path_piece.next_road = next_road;
}
