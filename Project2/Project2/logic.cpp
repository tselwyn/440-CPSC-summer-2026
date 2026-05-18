// logic.cpp - Game logic implementation
// Tyler Selwyn - CPSC 440 - Program 2

#include "logic.h"

ShapeType get_shape(ShapeType board[][COLS], int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return EMPTY;
    return board[row][col];
}

void set_shape(ShapeType board[][COLS], int row, int col, ShapeType shape) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;
    board[row][col] = shape;
}

bool compare(ShapeType board[][COLS], int r1, int c1, int r2, int c2) {
    return board[r1][c1] == board[r2][c2];
}

// clears all boards back to empty
void reset_game(ShapeType pattern[][COLS], ShapeType guess[][COLS], bool played[][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            pattern[r][c] = EMPTY;
            guess[r][c] = EMPTY;
            played[r][c] = false;
        }
    }
}