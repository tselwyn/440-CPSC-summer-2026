// graphics.h - Drawing and input functions
// Tyler Selwyn - CPSC 440 - Program 2

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "logic.h"

const int CELL_SIZE = 120;

void draw_grid();
void draw_objects(int x, int y, ShapeType shape);
void draw_status(ALLEGRO_FONT* font, int matched, int remaining);
void draw_matched(int x, int y);

void draw_circle_shape(int x, int y, ALLEGRO_COLOR color);
void draw_triangle_shape(int x, int y, ALLEGRO_COLOR color);
void draw_rectangle_shape(int x, int y, ALLEGRO_COLOR color);
void draw_diamond_shape(int x, int y, ALLEGRO_COLOR color);
void draw_oval_shape(int x, int y, ALLEGRO_COLOR color);
void draw_octagon_shape(int x, int y, ALLEGRO_COLOR color);
void draw_star_shape(int x, int y, ALLEGRO_COLOR color);
void draw_cross_shape(int x, int y, ALLEGRO_COLOR color);
void draw_arrow_shape(int x, int y, ALLEGRO_COLOR color);
void draw_hexagon_shape(int x, int y, ALLEGRO_COLOR color);
void draw_pentagon_shape(int x, int y, ALLEGRO_COLOR color);
void draw_heart_shape(int x, int y, ALLEGRO_COLOR color);

void get_mouse_input(int mx, int my, int& row, int& col);

#endif