// logic.cpp - Game logic implementation
// Tyler Selwyn - CPSC 440 - Program 2

#include "logic.h"
#include <cstdlib>
#include <ctime>

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

// fills the board with randomly placed pairs
void random_create(ShapeType pattern[][COLS], int num_pairs) {
    srand((unsigned)time(NULL));

    // each shape appears twice for pairs
    ShapeType shapes[24];
    for (int i = 0; i < num_pairs; i++) {
        shapes[i * 2] = (ShapeType)(i + 1);
        shapes[i * 2 + 1] = (ShapeType)(i + 1);
    }

    // Fisher-Yates shuffle
    for (int i = 23; i > 0; i--) {
        int j = rand() % (i + 1);
        ShapeType temp = shapes[i];
        shapes[i] = shapes[j];
        shapes[j] = temp;
    }

    // place into grid, bottom-right is status cell so skip it
    int index = 0;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (r == 4 && c == 4) {
                pattern[r][c] = EMPTY;
                continue;
            }
            pattern[r][c] = shapes[index];
            index++;
        }
    }
}