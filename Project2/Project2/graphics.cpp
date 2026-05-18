// graphics.cpp - Drawing and input implementation
// Tyler Selwyn - CPSC 440 - Program 2

#include "graphics.h"
#include <cmath>

void draw_grid() {
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    for (int i = 0; i <= COLS; i++) {
        al_draw_line(i * CELL_SIZE, 0, i * CELL_SIZE, ROWS * CELL_SIZE, white, 2);
    }

    for (int i = 0; i <= ROWS; i++) {
        al_draw_line(0, i * CELL_SIZE, COLS * CELL_SIZE, i * CELL_SIZE, white, 2);
    }
}

void get_mouse_input(int mx, int my, int& row, int& col) {
    col = mx / CELL_SIZE;
    row = my / CELL_SIZE;

    if (row < 0) row = 0;
    if (row >= ROWS) row = ROWS - 1;
    if (col < 0) col = 0;
    if (col >= COLS) col = COLS - 1;
}

void draw_circle_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x, y, 40, color);
}

void draw_triangle_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_triangle(x, y - 40, x - 40, y + 40, x + 40, y + 40, color);
}

void draw_rectangle_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x - 35, y - 25, x + 35, y + 25, color);
}

void draw_diamond_shape(int x, int y, ALLEGRO_COLOR color) {
    float points[8] = { (float)x, (float)(y - 40), (float)(x + 30), (float)y,
                         (float)x, (float)(y + 40), (float)(x - 30), (float)y };
    al_draw_filled_polygon(points, 4, color);
}

void draw_oval_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_ellipse(x, y, 40, 25, color);
}

void draw_octagon_shape(int x, int y, ALLEGRO_COLOR color) {
    float s = 18;
    float r = 40;
    float points[16] = {
        x - s, y - r,  x + s, y - r,
        x + r, y - s,  x + r, y + s,
        x + s, y + r,  x - s, y + r,
        x - r, y + s,  x - r, y - s
    };
    al_draw_filled_polygon(points, 8, color);
}

void draw_star_shape(int x, int y, ALLEGRO_COLOR color) {
    float outer = 40;
    float inner = 18;
    float points[20];
    for (int i = 0; i < 5; i++) {
        float angle_out = (i * 72 - 90) * 3.14159f / 180.0f;
        float angle_in = ((i * 72) + 36 - 90) * 3.14159f / 180.0f;
        points[i * 4] = x + outer * cos(angle_out);
        points[i * 4 + 1] = y + outer * sin(angle_out);
        points[i * 4 + 2] = x + inner * cos(angle_in);
        points[i * 4 + 3] = y + inner * sin(angle_in);
    }
    al_draw_filled_polygon(points, 10, color);
}

void draw_cross_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x - 10, y - 35, x + 10, y + 35, color);
    al_draw_filled_rectangle(x - 35, y - 10, x + 35, y + 10, color);
}

void draw_arrow_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_triangle(x, y - 40, x - 30, y, x + 30, y, color);
    al_draw_filled_rectangle(x - 12, y, x + 12, y + 35, color);
}

void draw_hexagon_shape(int x, int y, ALLEGRO_COLOR color) {
    float r = 38;
    float points[12];
    for (int i = 0; i < 6; i++) {
        float angle = (i * 60 - 30) * 3.14159f / 180.0f;
        points[i * 2] = x + r * cos(angle);
        points[i * 2 + 1] = y + r * sin(angle);
    }
    al_draw_filled_polygon(points, 6, color);
}

void draw_pentagon_shape(int x, int y, ALLEGRO_COLOR color) {
    float r = 38;
    float points[10];
    for (int i = 0; i < 5; i++) {
        float angle = (i * 72 - 90) * 3.14159f / 180.0f;
        points[i * 2] = x + r * cos(angle);
        points[i * 2 + 1] = y + r * sin(angle);
    }
    al_draw_filled_polygon(points, 5, color);
}

void draw_heart_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x - 18, y - 10, 20, color);
    al_draw_filled_circle(x + 18, y - 10, 20, color);
    al_draw_filled_triangle(x - 38, y - 2, x + 38, y - 2, x, y + 40, color);
}

// draws an X over matched cells
void draw_matched(int x, int y) {
    ALLEGRO_COLOR gray = al_map_rgb(100, 100, 100);
    al_draw_line(x - 35, y - 35, x + 35, y + 35, gray, 3);
    al_draw_line(x + 35, y - 35, x - 35, y + 35, gray, 3);
}

void draw_objects(int x, int y, ShapeType shape) {
    ALLEGRO_COLOR color;
    switch (shape) {
    case CIRCLE:    color = al_map_rgb(255, 0, 0); draw_circle_shape(x, y, color); break;
    case TRIANGLE:  color = al_map_rgb(0, 255, 0); draw_triangle_shape(x, y, color); break;
    case RECTANGLE: color = al_map_rgb(0, 0, 255); draw_rectangle_shape(x, y, color); break;
    case DIAMOND:   color = al_map_rgb(255, 255, 0); draw_diamond_shape(x, y, color); break;
    case OVAL:      color = al_map_rgb(255, 0, 255); draw_oval_shape(x, y, color); break;
    case OCTAGON:   color = al_map_rgb(0, 255, 255); draw_octagon_shape(x, y, color); break;
    case STAR:      color = al_map_rgb(255, 128, 0); draw_star_shape(x, y, color); break;
    case CROSS:     color = al_map_rgb(128, 255, 0); draw_cross_shape(x, y, color); break;
    case ARROW:     color = al_map_rgb(0, 128, 255); draw_arrow_shape(x, y, color); break;
    case HEXAGON:   color = al_map_rgb(255, 128, 128); draw_hexagon_shape(x, y, color); break;
    case PENTAGON:  color = al_map_rgb(128, 128, 255); draw_pentagon_shape(x, y, color); break;
    case HEART:     color = al_map_rgb(255, 64, 128); draw_heart_shape(x, y, color); break;
    default: break;
    }
}