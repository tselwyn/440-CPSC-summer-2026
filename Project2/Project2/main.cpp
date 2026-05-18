// main.cpp - Concentration/Memory Game
// Tyler Selwyn - CPSC 440 - Program 2

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "logic.h"
#include "graphics.h"

// only global variables per spec
int mx, my;

int main() {
    // init allegro and addons
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();

    ALLEGRO_DISPLAY* display = al_create_display(CELL_SIZE * COLS, CELL_SIZE * ROWS);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

    // register all event sources including display
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // game boards - pattern holds the answer, guess tracks reveals, played tracks matches
    ShapeType pattern[ROWS][COLS];
    ShapeType guess[ROWS][COLS];
    bool played[ROWS][COLS];

    reset_game(pattern, guess, played);
    random_create(pattern, TOTAL_PAIRS);

    int matched = 0;
    int remaining = TOTAL_PAIRS;
    bool done = false;
    ALLEGRO_EVENT ev;

    // track two click selections
    int first_row = -1, first_col = -1;
    int second_row = -1, second_col = -1;
    int click_count = 0;
    bool waiting = false;
    double wait_start = 0;

    // main game loop
    while (!done) {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
        }

        // handle mouse clicks
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mx = ev.mouse.x;
            my = ev.mouse.y;
            int row, col;
            get_mouse_input(mx, my, row, col);

            // if mismatch is on screen, this click clears it and starts new pair
            if (waiting) {
                waiting = false;
                click_count = 0;
                first_row = -1;
                first_col = -1;
                second_row = -1;
                second_col = -1;
            }

            if (row == 4 && col == 4) {
                // status cell, ignore
            }
            else if (played[row][col]) {
                // already matched, can't re-click
            }
            else if (click_count == 0) {
                // first card selection
                first_row = row;
                first_col = col;
                click_count = 1;
            }
            else if (click_count == 1) {
                if (row == first_row && col == first_col) {
                    // clicked same cell, ignore
                }
                else {
                    // second card selection
                    second_row = row;
                    second_col = col;
                    click_count = 2;

                    if (compare(pattern, first_row, first_col, second_row, second_col)) {
                        // match found
                        played[first_row][first_col] = true;
                        played[second_row][second_col] = true;
                        matched++;
                        remaining--;
                        click_count = 0;
                        first_row = -1;
                        first_col = -1;
                        second_row = -1;
                        second_col = -1;

                        // check if all pairs found
                        if (remaining == 0) {
                            al_clear_to_color(al_map_rgb(0, 0, 0));
                            al_draw_text(font, al_map_rgb(255, 255, 255),
                                CELL_SIZE * COLS / 2, CELL_SIZE * ROWS / 2,
                                ALLEGRO_ALIGN_CENTRE, "YOU WIN!");
                            al_flip_display();
                            al_rest(3);
                            done = true;
                        }
                    }
                    else {
                        // no match, start auto-hide timer
                        waiting = true;
                        wait_start = al_get_time();
                    }
                }
            }
        }

        // auto-hide mismatched cards after 1.5 seconds
        if (waiting && al_get_time() - wait_start >= 1.5) {
            waiting = false;
            click_count = 0;
            first_row = -1;
            first_col = -1;
            second_row = -1;
            second_col = -1;
        }

        // draw everything
        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_grid();

        // draw matched shapes with X over them
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

        // show first selected card
        if (click_count >= 1 && first_row >= 0) {
            int cx = first_col * CELL_SIZE + CELL_SIZE / 2;
            int cy = first_row * CELL_SIZE + CELL_SIZE / 2;
            draw_objects(cx, cy, pattern[first_row][first_col]);
        }

        // show second selected card
        if (click_count == 2 && second_row >= 0) {
            int cx = second_col * CELL_SIZE + CELL_SIZE / 2;
            int cy = second_row * CELL_SIZE + CELL_SIZE / 2;
            draw_objects(cx, cy, pattern[second_row][second_col]);
        }

        draw_status(font, matched, remaining);
        al_flip_display();
    }

    // cleanup
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}