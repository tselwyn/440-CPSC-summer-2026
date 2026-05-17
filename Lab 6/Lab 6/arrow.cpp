#include "arrow.h"
// Tyler Selwyn - CPSC 440 Lab 6
arrowClass::arrowClass()
{
	speed = 0;
	x = 100;
	y = 100;
	dir = 1;
	score = 0;
	for (int i = 0; i < 4; i++)
	{
		arrow_bmp[i] = NULL;
	}
}
arrowClass::~arrowClass()
{
	for (int i = 0; i < 4; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
}
void arrowClass::drawArrow()
{
	al_draw_bitmap(arrow_bmp[getDirection()], getX(), getY(), 0);
}

// Tyler Selwyn - replaced arrow with my spaceship from Lab 5
// 64x64 bitmap with 5 primitives and 3 colors
void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY* display)
{
	// Tyler Selwyn - ship colors
	ALLEGRO_COLOR silver = al_map_rgb(180, 190, 210);
	ALLEGRO_COLOR red = al_map_rgb(200, 40, 40);
	ALLEGRO_COLOR orange = al_map_rgb(240, 150, 30);

	for (int i = 0; i < 4; i++)
	{
		arrow_bmp[i] = al_create_bitmap(64, 64);
		if (!arrow_bmp[i]) {
			al_destroy_display(display);
			exit(1);
		}

		al_set_target_bitmap(arrow_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		// Tyler Selwyn - draw spaceship rotated for each direction
		switch (i)
		{
		case 0: // Up
			al_draw_filled_triangle(32, 4, 14, 48, 50, 48, silver);
			al_draw_filled_triangle(14, 48, 2, 60, 22, 42, silver);
			al_draw_filled_triangle(50, 48, 62, 60, 42, 42, silver);
			al_draw_filled_circle(32, 24, 7, red);
			al_draw_filled_rectangle(22, 48, 42, 56, orange);
			break;
		case 1: // Right
			al_draw_filled_triangle(60, 32, 16, 14, 16, 50, silver);
			al_draw_filled_triangle(16, 14, 4, 2, 22, 22, silver);
			al_draw_filled_triangle(16, 50, 4, 62, 22, 42, silver);
			al_draw_filled_circle(40, 32, 7, red);
			al_draw_filled_rectangle(8, 22, 16, 42, orange);
			break;
		case 2: // Down
			al_draw_filled_triangle(32, 60, 14, 16, 50, 16, silver);
			al_draw_filled_triangle(14, 16, 2, 4, 22, 22, silver);
			al_draw_filled_triangle(50, 16, 62, 4, 42, 22, silver);
			al_draw_filled_circle(32, 40, 7, red);
			al_draw_filled_rectangle(22, 8, 42, 16, orange);
			break;
		case 3: // Left
			al_draw_filled_triangle(4, 32, 48, 14, 48, 50, silver);
			al_draw_filled_triangle(48, 14, 60, 2, 42, 22, silver);
			al_draw_filled_triangle(48, 50, 60, 62, 42, 42, silver);
			al_draw_filled_circle(24, 32, 7, red);
			al_draw_filled_rectangle(48, 22, 56, 42, orange);
			break;
		}
	}
}

// Tyler Selwyn - updated erase to 64x64 to match new ship size
void arrowClass::erase_arrow()
{
	int left = x;
	int top = y;
	int right = x + 64;
	int bottom = y + 64;
	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
	dir = 0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::down()
{
	dir = 2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::left()
{
	dir = 3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::right()
{
	dir = 1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}
int arrowClass::getDirection()
{
	return dir;
}
int arrowClass::getSpeed()
{
	return speed;
}
int arrowClass::getX()
{
	return x;
}
int arrowClass::getY()
{
	return y;
}
void arrowClass::move_arrow(int width, int height)
{
	switch (dir)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
	}

	// Tyler Selwyn - updated bounds to 64 for bigger ship
	if (x > width - 64)
	{
		x = width - 64;
		speed = 0;
	}
	if (x < 0)
	{
		x = 0;
		speed = 0;
	}
	if (y > height - 64)
	{
		y = height - 64;
		speed = 0;
	}
	if (y < 0)
	{
		y = 0;
		speed = 0;
	}
}