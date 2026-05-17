#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>  // Tyler Selwyn - need font addon for text display
#include <cstdio>  // Tyler Selwyn - need this for sprintf_s
#include "arrow.h"
#include "bullet.h"

int main(void)
{
	arrowClass arrow;
	bullet mybullet[10];
	int score = 0;
	bool redraw = true;
	const int FPS = 60;

	int width = 640;
	int height = 520;  // Tyler Selwyn - made taller for info bar at bottom
	bool done = false;

	// Tyler Selwyn - timer and score display variables
	int countdown = 30;    // 30 second game timer
	int frameCount = 0;    // counts frames to track seconds
	ALLEGRO_FONT* font = NULL;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;

	al_install_keyboard();
	al_init_primitives_addon();

	// Tyler Selwyn - init font so we can print timer and score
	al_init_font_addon();
	font = al_create_builtin_font();

	arrow.create_arrow_bitmap(display);

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	arrow.drawArrow();
	al_flip_display();
	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			for (int i = 0;i < 10;i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
				}
			}

			// Tyler Selwyn - count frames to decrement the 30 sec timer
			frameCount++;
			if (frameCount >= 60) {
				frameCount = 0;
				countdown--;
				if (countdown <= 0)
					done = true;  // game over when timer runs out
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			 case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if (arrow.getSpeed() != 0) {
				arrow.erase_arrow();
				arrow.move_arrow(width, 480);  // Tyler Selwyn - keep arrow in gameplay area above info bar
			}
			arrow.drawArrow();
			for (int i = 0;i < 10;i++)
			{
				mybullet[i].erase_bullet();
				score += mybullet[i].move_bullet(arrow.getX(), arrow.getY(), 32, 32, 480);  // Tyler Selwyn - bullets stop at 480 not 520
			}

			// Tyler Selwyn - draw the info bar with timer and score
			 al_draw_filled_rectangle(0, 480, 640, 520, al_map_rgb(0, 0, 0));
			char timerText[50];
			char scoreText[50];
			sprintf_s(timerText, "Time: %d", countdown);
			sprintf_s(scoreText, "Score: %d", score);
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 490, 0, timerText);
			al_draw_text(font, al_map_rgb(255, 255, 255), 550, 490, 0, scoreText);
		}
		al_flip_display();
	}
	al_destroy_font(font);  // Tyler Selwyn - clean up font
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	system("pause");
	return 0;
}