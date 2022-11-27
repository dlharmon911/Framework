#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "app.h"

int32_t App::run(const std::vector<std::string>& argList)
{
	App app;

	if (app.init(argList) == 0)
	{
		app.loop();
	}

	app.shutdown();

	return 0;
}

App::App() : m_display(nullptr), m_queue(nullptr), m_timer(nullptr), m_kill(false), m_dirty(true), m_counter(0)
{
}

App::~App()
{
}

int32_t App::init(const std::vector<std::string>& argList)
{
	std::cout << "Initialization Begin" << std::endl;

	std::cout << "Initializing Allegro Library: ";
	if (!al_init())
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	std::cout << "Initializing Mouse: ";
	if (!al_install_mouse())
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	std::cout << "Initializing Keyboard: ";
	if (!al_install_keyboard())
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	std::cout << "Initializing Image Addon: ";
	if (!al_init_image_addon())
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	std::cout << "Creating Display: ";
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	if (!(this->m_display = al_create_display(App::SCREEN_W, App::SCREEN_H)))
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	ALLEGRO_BITMAP* icon = al_load_bitmap("data\\images\\icon.png");
	if (icon)
	{
		al_set_display_icon(this->m_display, icon);
		al_destroy_bitmap(icon);
	}
	al_set_window_title(this->m_display, App::APPNAME);

	std::cout << "Creating Event Queue: ";
	if (!(this->m_queue = al_create_event_queue()))
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	std::cout << "Creating Logic Timer: ";
	if (!(this->m_timer = al_create_timer(1.0/App::TIMING)))
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	std::cout << "pass" << std::endl;

	al_register_event_source(this->m_queue, al_get_display_event_source(this->m_display));
	al_register_event_source(this->m_queue, al_get_timer_event_source(this->m_timer));
	al_register_event_source(this->m_queue, al_get_keyboard_event_source());
	al_register_event_source(this->m_queue, al_get_mouse_event_source());

	al_start_timer(this->m_timer);

	std::cout << "Initialization Complete" << std::endl << std::endl;

	return 0;
}

void App::shutdown()
{
	std::cout << std::endl << "Shutdown Begin" << std::endl;

	if (this->m_timer)
	{
		al_stop_timer(this->m_timer);
		al_destroy_timer(this->m_timer);
		this->m_timer = nullptr;
		std::cout << "Timer Destroyed" << std::endl;
	}

	if (this->m_queue)
	{
		al_destroy_event_queue(this->m_queue);
		this->m_queue = nullptr;
		std::cout << "Queue Destroyed" << std::endl;
	}

	if (this->m_display)
	{
		al_destroy_display(this->m_display);
		this->m_display = nullptr;
		std::cout << "Display Destroyed" << std::endl;
	}

	std::cout << "Shutdown Complete" << std::endl << std::endl;
}

int32_t App::loop()
{
	while (!this->m_kill)
	{
		this->input();

		while (this->m_counter > 0)
		{
			this->logic();
			--this->m_counter;
		}

		if (this->m_dirty)
		{
			this->draw();
			this->m_dirty = false;
		}

		al_rest(0.01);
	}

	return 0;
}

void App::draw()
{
	al_clear_to_color(al_map_rgb(64, 0, 64));





	al_flip_display();
}

void App::logic()
{
}

void App::input()
{
	static ALLEGRO_EVENT event;

	while (!al_event_queue_is_empty(this->m_queue))
	{
		al_get_next_event(this->m_queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
		{
			++this->m_counter;
		} break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			this->m_kill = true;
		} break;
		}
	}
}

