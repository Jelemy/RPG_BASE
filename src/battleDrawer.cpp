#include <battleDrawer.h>
#include <textureManager.h>
#include <global.h>

battleDrawer::battleDrawer(entities &playerP, entities &enemyP)
{
    playerParty = playerP;
    enemyParty = enemyP;
    partyTurn = false;
    entityTurn = nullptr;
    text = new textManager();
    text->setFont("assets/glyphAtlas.png", 50, {255, 255, 255, 255});

	auto& uiMenu(manager.addEntity());
	auto& uiSubMenu(manager.addEntity());
	auto& uiPartyBox1(manager.addEntity());
	auto& uiPartyBox2(manager.addEntity());
	auto& uiArrow(manager.addEntity());
	auto& uiMessage(manager.addEntity());
	auto& bg(manager.addEntity());

    uiMenu.addComponent<tSpriteComponent>("assets/menubox.png", 40, 150);
	uiSubMenu.addComponent<tSpriteComponent>("assets/menuboxsub.png", 147, 150);
	uiPartyBox1.addComponent<tSpriteComponent>("assets/partyBox2.png", 147, 420);
	uiPartyBox2.addComponent<tSpriteComponent>("assets/partyBox2.png", 330, 420);
	uiArrow.addComponent<tSpriteComponent>("assets/arrow.png", 50, 193);
	uiMessage.addComponent<tSpriteComponent>("assets/dialoguebox.png", 121, 22);
	bg.addComponent<tSpriteComponent>("assets/plain.png", 0, 0);

    uiBoxes = {&uiMenu, &uiSubMenu, &uiPartyBox1, &uiPartyBox2, &uiMessage, &bg, &uiArrow};

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