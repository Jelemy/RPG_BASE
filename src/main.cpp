#include <game.h>
#include <titleState.h>

game *g = nullptr;

int main(int argc, char* argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    g = new game();
    TTF_Init();
    g->init("gameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);
    g->changeState(titleState::instance());

    // Main loop
    while (g->running()) {

        frameStart = SDL_GetTicks();
        g->handleEvents();
        g->update();
        g->draw();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        
    }
    g->clean();
    return 0;

}