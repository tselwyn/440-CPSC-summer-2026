#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
int main() {
	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	// background 
	   //    background
	al_clear_to_color(al_map_rgb(135, 206, 235));

	//  body -  rectangle
	al_draw_filled_rectangle(200, 200, 450, 400, al_map_rgb(139, 69, 19));
	//  - roof for house 
	al_draw_filled_triangle(180, 200, 470, 200, 325, 100, al_map_rgb(178, 34, 34));









}