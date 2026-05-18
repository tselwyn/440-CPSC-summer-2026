// main.cpp - Concentration/Memory Game
// Tyler Selwyn - CPSC 440 - Program 2

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "logic.h"
#include "graphics.h"

int mx, my;

int main() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();

    ALLEGRO_DISPLAY* display = al_create_display(CELL_SIZE * COLS, CELL_SIZE * ROWS);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    ShapeType pattern[ROWS][COLS];
    ShapeType guess[ROWS][COLS];
    bool played[ROWS][COLS];

    reset_game(pattern, guess, played);
    random_create(pattern, TOTAL_PAIRS);

    int matched = 0;
    int remaining = TOTAL_PAIRS;
    bool done = false;
    ALLEGRO_EVENT ev;

    int first_row = -1, first_col = -1;
    int second_row = -1, second_col = -1;
    int click_count = 0;
    bool waiting = false;
    double wait_start = 0;

    while (!done) {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
        }

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !waiting) {
            mx = ev.mouse.x;
            my = ev.mouse.y;
            int row, col;
            get_mouse_input(mx, my, row, col);

            if (row == 4 && col == 4) {
                // status cell, ignore
            }
            else if (played[row][col]) {
                // already matched
            }
            else if (click_count == 0) {
                first_row = row;
                first_col = col;
                click_count = 1;
            }
            else if (click_count == 1) {
                if (row == first_row && col == first_col) {
                    // same cell, ignore
                }
                else {
                    second_row = row;
                    second_col = col;
                    click_count = 2;

                    if (compare(pattern, first_row, first_col, second_row, second_col)) {
                        played[first_row][first_col] = true;
                        played[second_row][second_col] = true;
                        matched++;
                        remaining--;
                        click_count = 0;
                    }
                    else {
                        waiting = true;
                        wait_start = al_get_time();
                    }
                }
            }
        }

        // 5 second timer for mismatches
        if (waiting && al_get_time() - wait_start >= 5.0) {
            waiting = false;
            click_count = 0;
            first_row = -1;
            first_col = -1;
            second_row = -1;
            second_col = -1;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_grid();

        // draw matched shapes with X
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (played[r][c]) {
                    int cx = c * CELL_SIZE + CELL_SIZE / 2;
                    int cy = r * CELL_SIZE + CELL_SIZE / 2;
                    draw_objects(cx, cy, pattern[r][c]);
                    draw_matched(cx, cy);
                }
            }
        }

        // show first click
        if (click_count >= 1 && first_row >= 0) {
            int cx = first_col * CELL_SIZE + CELL_SIZE / 2;
            int cy = first_row * CELL_SIZE + CELL_SIZE / 2;
            draw_objects(cx, cy, pattern[first_row][first_col]);
        }

        // show second click
        if (click_count == 2 && second_row >= 0) {
            int cx = second_col * CELL_SIZE + CELL_SIZE / 2;
            int cy = second_row * CELL_SIZE + CELL_SIZE / 2;
            draw_objects(cx, cy, pattern[second_row][second_col]);
        }

        al_flip_display();
    }

    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}