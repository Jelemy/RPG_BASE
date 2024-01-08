#include <game.h>
#include <gamestate.h>
#include <iostream>



SDL_Renderer* game::renderer = nullptr;

game::game()
{}
game::~game()
{}

void game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised..." << std::endl;
        // Create window with specified position, dimensions and flags
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }
        // Create renderer. Returns valid rendering context pointer 
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) 
        {
            // set the color used for drawing operations (rect, line and clear)
            //doesnt affect program
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    }
}

// Destroy window, clears all the states
void game::clean()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->clean();
		states.pop_back();
	}
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}


// The current state is always the last state in the list (the most recently added)

// If a state list is empty, we clean the current state and pop it.
// Otherwise push the state that is passed in.
void game::changeState(gameState* state) 
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->clean();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->init();
}

// Pushes a new state into the states list
void game::pushState(gameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->init();
}

// pop's off the current state
void game::popState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->clean();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->resume();
	}
}

void game::handleEvents()
{
    states.back()->handleEvents(this);
}

void game::update()
{
    states.back()->update(this);
}

// Rendering everything
void game::draw()
{
    states.back()->draw(this);
}





