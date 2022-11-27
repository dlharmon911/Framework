#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <allegro5/allegro.h>
#include <vector>
#include <string>

class App
{
public:

	/**
	Runs the program.
	@param arglist - command line arguments
	@return 0 with no errors, negative on error
	*/
	static int32_t run(const std::vector<std::string>& argList);

private:

	/**
	App class constructor
	@param none
	@return none
	*/
	App();

	/**
	App class deconstructor
	@param none
	@return none
	*/
	~App();

	/**
	Initializes applaction
	@param arglist - command line arguments
	@return 0 with no errors, negative on error
	*/
	int32_t init(const std::vector<std::string>& argList);

	/**
	Shutdown and deinitialze everything
	@param none
	@return none
	*/
	void shutdown();

	/**
	Basic loop of input/logic/draw
	@param none
	@return 0 with no errors, negative on error
	*/
	int32_t loop();

	/**
	Output to the screen
	@param none
	@return none
	*/
	void draw();

	/**
	Process all logic
	@param none
	@return none
	*/
	void logic();

	/**
	Process any incoming events
	@param none
	@return none
	*/
	void input();

	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_EVENT_QUEUE* m_queue;
	ALLEGRO_TIMER* m_timer;
	bool m_kill;
	bool m_dirty;
	int32_t m_counter;

	const int32_t SCREEN_W = 800;
	const int32_t SCREEN_H = 600;
	const double TIMING = 60.0;
	const char* APPNAME = "This is My NAME";
};

#endif // !_APPLICATION_H_

