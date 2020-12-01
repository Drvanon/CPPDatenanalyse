#include "path.h"

PathPool::PathPool(int size): Pool<PathPiece>(size) {}

void new_path_piece(int path_id, int prev_path, int next_path) {
    PathPiece path_piece;
    path_piece.id = path_id;
    path_piece.prev_path = path_prev_path;
    path_piece.next_path = path_next_path;
}
