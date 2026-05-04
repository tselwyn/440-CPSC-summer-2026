#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
// Tyler Selwyn
// CPSC 440 - Game Programming
// Lab 1 - Drawing with Allegro Primitives
// This program draws a house scene using Allegro 5 primitives
int main() {
	al_init();
	al_init_primitives_addon();
	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	
	   //    background
	al_clear_to_color(al_map_rgb(135, 206, 235));

	//  body -  rectangle
	al_draw_filled_rectangle(200, 200, 450, 400, al_map_rgb(139, 69, 19));
	//  - roof for house 

	al_draw_filled_triangle(180, 200, 470, 200, 325, 100, al_map_rgb(178, 34, 34));


	// Door - rectangle
	al_draw_filled_rectangle(290, 300, 360, 400, al_map_rgb(85, 45, 10));

	// Sun -  circle
	al_draw_filled_circle(550, 80, 50, al_map_rgb(255, 255, 0));

	al_flip_display();
	al_rest(5.0);
	al_destroy_display(display);

	return 0;







}