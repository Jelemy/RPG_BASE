#ifndef game_h
#define game_h

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "textureManager.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class gameState;

class game {

public:
    game();
    ~game();

    static SDL_Renderer* renderer;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void clean();

	void changeState(gameState* state);
	void pushState(gameState* state);
	void popState();

    void handleEvents();
    void update();
    void draw();

    bool running() {return isRunning;}
    void quit() { isRunning = false; }

private:
    vector<gameState*> states;
    bool isRunning;
    SDL_Window *window;
};
#endif
