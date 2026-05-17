#include "bullet.h"
// Tyler Selwyn - CPSC 440 Lab 6
bullet::bullet()
{
	alive = false;
	bullet_bmp = NULL;
	srand(time(0));
}
bool bullet::getStatus()
{
	return alive;
}

// Tyler Selwyn - create a 16x16 bullet bitmap with 2 primitives and 2 colors
void bullet::create_bullet_bitmap(ALLEGRO_DISPLAY* display)
{
	bullet_bmp = al_create_bitmap(16, 16);
	if (!bullet_bmp) {
		al_destroy_display(display);
		exit(1);
	}
	al_set_target_bitmap(bullet_bmp);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// Tyler Selwyn - red circle with a yellow diamond on top
	al_draw_filled_circle(8, 8, 7, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(8, 1, 15, 8, 1, 8, al_map_rgb(255, 255, 0));

	al_set_target_backbuffer(display);
}

void bullet::fire()
{
	x = rand() % 615 + 10;
	y = 10;
	alive = true;
}

// Tyler Selwyn - erase using bitmap size now (16x16 instead of 5x5)
void bullet::erase_bullet()
{
	al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0));
}

// Tyler Selwyn - draw bitmap instead of rectangle, adjusted collision to 16x16
int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	al_draw_bitmap(bullet_bmp, x, y, 0);

	if (x > arrowX && x < arrowX + width && y > arrowY && y < arrowY + length) {
		al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0));
		alive = false;
		return 1;
	}
	if (y > height)
		alive = false;
	return 0;
}