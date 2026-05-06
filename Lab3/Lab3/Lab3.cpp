// Tyler Selwyn
// CPSC 440 - Lab 3
// Mouse input with quadrant-based color changes 5/5/2026

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

int main() {
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();

    int width = 640;
    int height = 480;
    ALLEGRO_DISPLAY* display = al_create_display(width, height);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // object starts at center
    int pos_x = width / 2;
    int pos_y = height / 2;

    // default colors
    ALLEGRO_COLOR bg_color = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);

    bool done = false;
    ALLEGRO_EVENT ev;
    char coord_text[50];

   