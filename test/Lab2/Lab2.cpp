#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
// Tyler Selwyn
// CPSC 440 - Lab 2
// Moving object with directional pointer using keyboard input

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    // starting position is center of screen 
    int pos_x = 320;
    int pos_y = 240;
    int direction = 0;
    bool done = false;
    ALLEGRO_EVENT ev;

    //while loop for  keys 
    while (!done) {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                pos_y -= 10;
                direction = 0;
                break;
            case ALLEGRO_KEY_DOWN:
                pos_y += 10;
                direction = 1;
                break;
            case ALLEGRO_KEY_RIGHT:
                pos_x += 10;
                direction = 2;
                break;
            case ALLEGRO_KEY_LEFT:
                pos_x -= 10;
                direction = 3;
                break;
            case ALLEGRO_KEY_U:
                pos_x -= 10;
                pos_y -= 10;
                direction = 4;
                break;
            case ALLEGRO_KEY_D:
                pos_x += 10;
                pos_y += 10;
                direction = 5;
                break;
            case ALLEGRO_KEY_R:
                pos_x += 10;
                pos_y -= 10;
                direction = 6;
                break;
            case ALLEGRO_KEY_L:
                pos_x -= 10;
                pos_y += 10;
                direction = 7;
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_filled_circle(pos_x, pos_y, 20, al_map_rgb(0, 255, 0));


        // pointer showing direction 
        if (direction == 0) // up
            al_draw_line(pos_x, pos_y, pos_x, pos_y - 30, al_map_rgb(255, 255, 0), 3);
        else if (direction == 1) // down
            al_draw_line(pos_x, pos_y, pos_x, pos_y + 30, al_map_rgb(255, 255, 0), 3);
        else if (direction == 2) // right
            al_draw_line(pos_x, pos_y, pos_x + 30, pos_y, al_map_rgb(255, 255, 0), 3);
        else if (direction == 3) // left
            al_draw_line(pos_x, pos_y, pos_x - 30, pos_y, al_map_rgb(255, 255, 0), 3);
        else if (direction == 4) // upper left
            al_draw_line(pos_x, pos_y, pos_x - 25, pos_y - 25, al_map_rgb(255, 255, 0), 3);
        else if (direction == 5) // lower right
            al_draw_line(pos_x, pos_y, pos_x + 25, pos_y + 25, al_map_rgb(255, 255, 0), 3);
        else if (direction == 6) // upper right
            al_draw_line(pos_x, pos_y, pos_x + 25, pos_y - 25, al_map_rgb(255, 255, 0), 3);
        else if (direction == 7) // lower left
            al_draw_line(pos_x, pos_y, pos_x - 25, pos_y + 25, al_map_rgb(255, 255, 0), 3);

        al_flip_display();
    }

    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}


  