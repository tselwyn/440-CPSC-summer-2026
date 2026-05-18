// logic.h - Game logic for Concentration/Memory game
// Tyler Selwyn - CPSC 440 - Program 2

#ifndef LOGIC_H
#define LOGIC_H

// Shape types for the game pieces
enum ShapeType {
    EMPTY,
    CIRCLE,
    TRIANGLE,
    RECTANGLE,
    DIAMOND,
    OVAL,
    OCTAGON,
    STAR,
    CROSS,
    ARROW,
    HEXAGON,
    PENTAGON,
    HEART
};

const int ROWS = 5;
const int COLS = 5;
const int TOTAL_PAIRS = 12;

// Get shape at a given row/col from a board
ShapeType get_shape(ShapeType board[][COLS], int row, int col);

// Set shape at a given row/col on a board
void set_shape(ShapeType board[][COLS], int row, int col, ShapeType shape);

// Compare two selected cells
bool compare(ShapeType board[][COLS], int r1, int c1, int r2, int c2);

// Reset/clear all game boards
void reset_game(ShapeType pattern[][COLS], ShapeType guess[][COLS], bool played[][COLS]);

// Randomly place pairs on the pattern board
void random_create(ShapeType pattern[][COLS], int num_pairs);

#endif
