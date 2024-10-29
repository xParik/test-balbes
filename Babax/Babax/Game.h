#pragma once
#include <SDL.h>
#include "Maze.h"
#include "Player.h"

class Game{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Maze maze;
	Player player;
public:
	Game();
	~Game();
	void run();
};

