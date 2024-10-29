#pragma once
#include <SDL.h>
#include "Maze.h"

class Player {
private:
    SDL_Rect rect;
    Maze* maze;
public:
    Player(int startX, int startY, Maze* m);
    void move(int dx, int dy);
    bool hasReachedExit();
    void draw(SDL_Renderer* renderer);
};