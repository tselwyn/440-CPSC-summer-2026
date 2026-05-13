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
