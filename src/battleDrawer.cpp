#include <battleDrawer.h>


battleDrawer::battleDrawer(entities &playerP, entities &enemyP, entities &ui)
{
    playerParty = playerP;
    enemyParty = enemyP;
    uiBoxes = ui;
    partyTurn = false;
    entityTurn = nullptr;
    text = new textManager();
    text->setFont("assets/glyphAtlas.png", 50, {255, 255, 255, 255});

}

void battleDrawer::setTurn(Entity* e){
    entityTurn = e;
}
void battleDrawer::drawMenu(){
    uiBoxes[0]->getComponent<tSpriteComponent>().draw();

    text->displayText("Bash", uiBoxes[0]->getComponent<tSpriteComponent>().getX() + 25, uiBoxes[0]->getComponent<tSpriteComponent>().getY() + 40);
    text->displayText("Art", uiBoxes[0]->getComponent<tSpriteComponent>().getX() + 25, uiBoxes[0]->getComponent<tSpriteComponent>().getY() + 60);
    /*
    SDL_Color white = {255, 255, 255, 255};
    TTF_Font* font = TTF_OpenFont("assets/Thintel.ttf", 20);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, "Fight\nRun", white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game::renderer, textSurf);
    SDL_Rect srcRect, destRect;
    srcRect.w = 100;
    srcRect.h = 20;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = 40;
    destRect.h = 50;
    destRect.x = uiBoxes[0]->getComponent<tSpriteComponent>().getX() + 25;
    destRect.y = uiBoxes[0]->getComponent<tSpriteComponent>().getY() + 40;
    SDL_RenderCopy(game::renderer, textTexture, &srcRect, & destRect);
    */
}

void battleDrawer::drawText(string txt){
    text->displayText(txt, uiBoxes[4]->getComponent<tSpriteComponent>().getX() + 25, uiBoxes[4]->getComponent<tSpriteComponent>().getY() + 40);
}
void battleDrawer::drawSubMenu(){
    uiBoxes[1]->getComponent<tSpriteComponent>().draw();
}
void battleDrawer::drawPartyBox(){
    uiBoxes[2]->getComponent<tSpriteComponent>().draw();
    uiBoxes[3]->getComponent<tSpriteComponent>().draw();
}
void battleDrawer::drawMessage(){
    uiBoxes[4]->getComponent<tSpriteComponent>().draw();
}
void battleDrawer::drawBG(){
    uiBoxes[5]->getComponent<tSpriteComponent>().draw();
}
void battleDrawer::drawSelect(int move){
    
    int currY = uiBoxes[6]->getComponent<tSpriteComponent>().getY();
    uiBoxes[6]->getComponent<tSpriteComponent>().setY(currY + (move * 21));

 
    
    uiBoxes[6]->getComponent<tSpriteComponent>().draw();
}