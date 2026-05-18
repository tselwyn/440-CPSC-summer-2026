// logic.h - Game logic for Concentration/Memory game
// Tyler Selwyn - CPSC 440 - Program 2

#ifndef LOGIC_H
#define LOGIC_H

// 12 shapes + EMPTY for the status cell
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

// board dimensions
const int ROWS = 5;
const int COLS = 5;
const int TOTAL_PAIRS = 12;

// game logic functions
ShapeType get_shape(ShapeType board[][COLS], int row, int col);
void set_shape(ShapeType board[][COLS], int row, int col, ShapeType shape);
bool compare(ShapeType board[][COLS], int r1, int c1, int r2, int c2);
void reset_game(ShapeType pattern[][COLS], ShapeType guess[][COLS], bool played[][COLS]);
void random_create(ShapeType pattern[][COLS], int num_pairs);

#endif