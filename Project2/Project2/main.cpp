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

    // register all event sources including display
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

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

        // handle mouse clicks, blocked during mismatch wait
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
                // first card selection
                first_row = row;
                first_col = col;
                click_count = 1;
            }
            else if (click_count == 1) {
                if (row == first_row && col == first_col) {
                    // same cell, ignore
                }
                else {
                    // second card selection
                    second_row = row;
                    second_col = col;
                    click_count = 2;