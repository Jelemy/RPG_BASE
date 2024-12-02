// file created so that the keyboard controller can access fields in overWorldState class
#include "cKeyboardController.h"
#include "overWorldState.h"

void KeyboardController::init() {
    transform = &entity->getComponent<transformComponent>();
}

void KeyboardController::update() {

    SDL_Event& event = overWorldState::getEvent();

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                transform->velocity.y = -1;
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                break;
            default:
                break;
        }
    }

    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                transform->velocity.y = 0;
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            default:
                break;
        }
    }
}
