#include <battleDrawer.h>
#include <textureManager.h>
#include <global.h>

battleDrawer::battleDrawer()
{
    partyTurn = false;
    entityTurn = nullptr;
    text = new textManager();
    text->setFont("assets/glyphAtlas.png", 50, {255, 255, 255, 255});

	auto& uiMenu(manager.addEntity());
	auto& uiSubMenu(manager.addEntity());
	auto& uiPartyBox1(manager.addEntity());
	auto& uiPartyBox2(manager.addEntity());
	auto& uiArrow(manager.addEntity());
    auto& uiArrow2(manager.addEntity());
    auto& uiArrowDown(manager.addEntity());
	auto& uiMessage(manager.addEntity());
	auto& bg(manager.addEntity());

    uiMenu.addComponent<tSpriteComponent>("assets/menubox.png", 20, 150);
	uiSubMenu.addComponent<tSpriteComponent>("assets/subMenuLarge.png", 127, 150);
	uiPartyBox1.addComponent<tSpriteComponent>("assets/partyBox2.png", 147, 420);
	uiPartyBox2.addComponent<tSpriteComponent>("assets/partyBox2.png", 330, 420);
	uiArrow.addComponent<tSpriteComponent>("assets/arrow.png", 30, 199);
    uiArrow2.addComponent<tSpriteComponent>("assets/arrow.png", 145, 176);
    uiArrowDown.addComponent<tSpriteComponent>("assets/arrow_down.png", 0, 0);
	uiMessage.addComponent<tSpriteComponent>("assets/dialoguebox.png", 121, 22);
	bg.addComponent<tSpriteComponent>("assets/plain.png", 0, 0);

    uiBoxes = {&uiMenu, &uiSubMenu, &uiPartyBox1, &uiPartyBox2, &uiMessage, &bg, &uiArrow, &uiArrow2, &uiArrowDown};

}

void battleDrawer::setTurn(Entity* e){
    entityTurn = e;
}
void battleDrawer::drawMenu(){
    uiBoxes[0]->getComponent<tSpriteComponent>().draw();

    text->displayText("Bash", uiBoxes[0]->getComponent<tSpriteComponent>().getX() + 25, uiBoxes[0]->getComponent<tSpriteComponent>().getY() + 45);
    text->displayText("Art", uiBoxes[0]->getComponent<tSpriteComponent>().getX() + 25, uiBoxes[0]->getComponent<tSpriteComponent>().getY() + 65);
}

void battleDrawer::drawText(string txt){
    text->displayText(txt, uiBoxes[4]->getComponent<tSpriteComponent>().getX() + 25, uiBoxes[4]->getComponent<tSpriteComponent>().getY() + 40);
}
void battleDrawer::drawSubMenu(int currPlayer){

    uiBoxes[1]->getComponent<tSpriteComponent>().draw();
    arts artList = playerParty[currPlayer]->getComponent<statsComponent>().art();
    int displace = 22;
    for (string art : artList) {
        int x = uiBoxes[1]->getComponent<tSpriteComponent>().getX() + 28;
        int y = displace + uiBoxes[0]->getComponent<tSpriteComponent>().getY();
        text->displayText(art, x, y);
        displace += 20;
    }

}
void battleDrawer::drawPartyBox(){
    string name1 = playerParty[0]->getComponent<statsComponent>().nme();
    string HP1 = "HP:" + to_string(playerParty[0]->getComponent<statsComponent>().HP());
    string MP1 = "MP:" + to_string(playerParty[0]->getComponent<statsComponent>().MP());
    

    string name2 = playerParty[1]->getComponent<statsComponent>().nme();
    string HP2 = "HP:" + to_string(playerParty[1]->getComponent<statsComponent>().HP());
    string MP2 = "MP:" + to_string(playerParty[1]->getComponent<statsComponent>().MP());

    uiBoxes[2]->getComponent<tSpriteComponent>().draw();
    text->displayText(name1, uiBoxes[2]->getComponent<tSpriteComponent>().getX() + 20, uiBoxes[2]->getComponent<tSpriteComponent>().getY() + 7);
    text->displayText(HP1, uiBoxes[2]->getComponent<tSpriteComponent>().getX() + 15, uiBoxes[2]->getComponent<tSpriteComponent>().getY() + 37);
    text->displayText(MP1, uiBoxes[2]->getComponent<tSpriteComponent>().getX() + 110, uiBoxes[2]->getComponent<tSpriteComponent>().getY() + 37);

    uiBoxes[3]->getComponent<tSpriteComponent>().draw();
    text->displayText(name2, uiBoxes[3]->getComponent<tSpriteComponent>().getX() + 20, uiBoxes[3]->getComponent<tSpriteComponent>().getY() + 7);
    text->displayText(HP2, uiBoxes[3]->getComponent<tSpriteComponent>().getX() + 15, uiBoxes[2]->getComponent<tSpriteComponent>().getY() + 37);
    text->displayText(MP2, uiBoxes[3]->getComponent<tSpriteComponent>().getX() + 110, uiBoxes[2]->getComponent<tSpriteComponent>().getY() + 37);
}

void battleDrawer::drawEnemy(){
    enemyParty[0]->getComponent<tSpriteComponent>().draw();
    enemyParty[1]->getComponent<tSpriteComponent>().draw();
}

void battleDrawer::drawMessage(){
    uiBoxes[4]->getComponent<tSpriteComponent>().draw();
}
void battleDrawer::drawBG(){
    uiBoxes[5]->getComponent<tSpriteComponent>().draw();
}
void battleDrawer::drawSelect(int move, int action, menuLayer menu){
    if (menu == ACT) {
        int currY = uiBoxes[6]->getComponent<tSpriteComponent>().getY();
        if (action == 0) {
             uiBoxes[6]->getComponent<tSpriteComponent>().setY(199);
        } else {
             uiBoxes[6]->getComponent<tSpriteComponent>().setY(currY + (move * 20));
        }
        uiBoxes[6]->getComponent<tSpriteComponent>().draw();
    }
    else if (menu == ART) {
        int currY = uiBoxes[7]->getComponent<tSpriteComponent>().getY();
        if (action == 0) {
             uiBoxes[7]->getComponent<tSpriteComponent>().setY(176);
        } else {
             uiBoxes[7]->getComponent<tSpriteComponent>().setY(currY + (move * 20));
        }
        uiBoxes[7]->getComponent<tSpriteComponent>().draw();
    }
    else {
        
        int currY = uiBoxes[8]->getComponent<tSpriteComponent>().getY();
        int enemyX = enemyParty[action]->getComponent<tSpriteComponent>().getX();
        int enemyY = enemyParty[action]->getComponent<tSpriteComponent>().getY();
        uiBoxes[8]->getComponent<tSpriteComponent>().setX(enemyX + 90);
        uiBoxes[8]->getComponent<tSpriteComponent>().setY(enemyY - 10);
        uiBoxes[8]->getComponent<tSpriteComponent>().draw();
        
        
    }
}