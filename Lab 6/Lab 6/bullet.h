#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
// Tyler Selwyn - CPSC 440 Lab 6

class bullet
{
public:
	bullet();
	void fire();
	int move_bullet(int arrowX, int arrowY, int width, int length, int height);
	void erase_bullet();
	bool getStatus();
	void create_bullet_bitmap(ALLEGRO_DISPLAY* display);  // Tyler Selwyn - create custom bullet sprite
private:
	int x, y;
	bool alive;
	ALLEGRO_BITMAP* bullet_bmp;  // Tyler Selwyn - bitmap for custom bullet
};