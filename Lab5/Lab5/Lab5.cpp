#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    int width = 640;
    int height = 480;
    ALLEGRO_DISPLAY* display = al_create_display(width, height);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // create a 64x64 bitmap for the spaceship
    ALLEGRO_BITMAP* ship = al_create_bitmap(64, 64);


    // switch drawing target to the bitmap
    al_set_target_bitmap(ship);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0)); // transparent background

    // --- COLORS ---
    ALLEGRO_COLOR silver = al_map_rgb(180, 190, 210);
    ALLEGRO_COLOR red = al_map_rgb(200, 40, 40);
    ALLEGRO_COLOR orange = al_map_rgb(240, 150, 30);

    // 1) main body - filled triangle pointing up
    al_draw_filled_triangle(32, 4, 14, 48, 50, 48, silver);

    // 2) left wing - filled triangle
    al_draw_filled_triangle(14, 48, 2, 60, 22, 42, silver);

    // 3) right wing - filled triangle
    al_draw_filled_triangle(50, 48, 62, 60, 42, 42, silver);

    // 4) cockpit window - filled circle
    al_draw_filled_circle(32, 24, 7, red);

    // 5) engine glow - filled rectangle
    al_draw_filled_rectangle(22, 48, 42, 56, orange);

    // switch drawing back to the display
    al_set_target_backbuffer(display);

    bool done = false;
    ALLEGRO_EVENT ev;