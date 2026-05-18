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

    // game boards
    ShapeType pattern[ROWS][COLS];
    ShapeType guess[ROWS][COLS];
    bool played[ROWS][COLS];

    reset_game(pattern, guess, played);
    random_create(pattern, TOTAL_PAIRS);

    int matched = 0;
    int remaining = TOTAL_PAIRS;
    bool done = false;
    ALLEGRO_EVENT ev;

    while (!done) {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
        }

        // draw
        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_grid();
        al_flip_display();
    }

    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}