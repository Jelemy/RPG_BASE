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

    uiMenu.addComponent<bSpriteComponent>("assets/menubox.png", 20, 150);
	uiSubMenu.addComponent<bSpriteComponent>("assets/subMenuLarge.png", 127, 150);
	uiPartyBox1.addComponent<bSpriteComponent>("assets/partyBox2.png", 147, 420);
	uiPartyBox2.addComponent<bSpriteComponent>("assets/partyBox2.png", 330, 420);
	uiArrow.addComponent<bSpriteComponent>("assets/arrow.png", 30, 199);
    uiArrow2.addComponent<bSpriteComponent>("assets/arrow.png", 145, 176);
    uiArrowDown.addComponent<bSpriteComponent>("assets/arrow_down.png", 0, 0);
	uiMessage.addComponent<bSpriteComponent>("assets/dialoguebox.png", 121, 22);
	bg.addComponent<bSpriteComponent>("assets/plain.png", 0, 0);

    uiBoxes = {&uiMenu, &uiSubMenu, &uiPartyBox1, &uiPartyBox2, &uiMessage, &bg, &uiArrow, &uiArrow2, &uiArrowDown};

}

void battleDrawer::setTurn(Entity* e){
    entityTurn = e;
}
void battleDrawer::drawMenu(int currPlayer){
    uiBoxes[0]->getComponent<bSpriteComponent>().draw();
    text->displayText(playerParty[currPlayer]->getComponent<statsComponent>().nme(), uiBoxes[0]->getComponent<bSpriteComponent>().getX() + 20, uiBoxes[0]->getComponent<bSpriteComponent>().getY() + 10);
    text->displayText("Bash", uiBoxes[0]->getComponent<bSpriteComponent>().getX() + 25, uiBoxes[0]->getComponent<bSpriteComponent>().getY() + 45);
    text->displayText("Art", uiBoxes[0]->getComponent<bSpriteComponent>().getX() + 25, uiBoxes[0]->getComponent<bSpriteComponent>().getY() + 65);
}

void battleDrawer::drawText(string txt){
    text->displayText(txt, uiBoxes[4]->getComponent<bSpriteComponent>().getX() + 25, uiBoxes[4]->getComponent<bSpriteComponent>().getY() + 20);
}
void battleDrawer::drawSubMenu(int currPlayer){

    uiBoxes[1]->getComponent<bSpriteComponent>().draw();
    arts artList = playerParty[currPlayer]->getComponent<statsComponent>().art();
    int displace = 22;
    for (string art : artList) {
        int x = uiBoxes[1]->getComponent<bSpriteComponent>().getX() + 28;
        int y = displace + uiBoxes[0]->getComponent<bSpriteComponent>().getY();
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

    uiBoxes[2]->getComponent<bSpriteComponent>().draw();
    text->displayText(name1, uiBoxes[2]->getComponent<bSpriteComponent>().getX() + 20, uiBoxes[2]->getComponent<bSpriteComponent>().getY() + 7);
    text->displayText(HP1, uiBoxes[2]->getComponent<bSpriteComponent>().getX() + 15, uiBoxes[2]->getComponent<bSpriteComponent>().getY() + 37);
    text->displayText(MP1, uiBoxes[2]->getComponent<bSpriteComponent>().getX() + 110, uiBoxes[2]->getComponent<bSpriteComponent>().getY() + 37);

    uiBoxes[3]->getComponent<bSpriteComponent>().draw();
    text->displayText(name2, uiBoxes[3]->getComponent<bSpriteComponent>().getX() + 20, uiBoxes[3]->getComponent<bSpriteComponent>().getY() + 7);
    text->displayText(HP2, uiBoxes[3]->getComponent<bSpriteComponent>().getX() + 15, uiBoxes[2]->getComponent<bSpriteComponent>().getY() + 37);
    text->displayText(MP2, uiBoxes[3]->getComponent<bSpriteComponent>().getX() + 110, uiBoxes[2]->getComponent<bSpriteComponent>().getY() + 37);
}

void battleDrawer::drawEnemy(){
    for (Entity* enemy: enemyParty) {
        enemy->getComponent<bSpriteComponent>().draw();                    
    }
}

void battleDrawer::drawMessage(){
    uiBoxes[4]->getComponent<bSpriteComponent>().draw();
}
void battleDrawer::drawBG(){
    uiBoxes[5]->getComponent<bSpriteComponent>().draw();
}
void battleDrawer::drawSelect(int move, int action, menuLayer menu){
    if (menu == ACT) {
        int currY = uiBoxes[6]->getComponent<bSpriteComponent>().getY();
        if (action == 0) {
             uiBoxes[6]->getComponent<bSpriteComponent>().setY(199);
        } else {
             uiBoxes[6]->getComponent<bSpriteComponent>().setY(currY + (move * 20));
        }
        uiBoxes[6]->getComponent<bSpriteComponent>().draw();
    }
    else if (menu == ART) {
        int currY = uiBoxes[7]->getComponent<bSpriteComponent>().getY();
        if (action == 0) {
             uiBoxes[7]->getComponent<bSpriteComponent>().setY(176);
        } else {
             uiBoxes[7]->getComponent<bSpriteComponent>().setY(currY + (move * 20));
        }
        uiBoxes[7]->getComponent<bSpriteComponent>().draw();
    }
    else if (menu == ENEMY) {
        
        int currY = uiBoxes[8]->getComponent<bSpriteComponent>().getY();
        int enemyX = enemyParty[action]->getComponent<bSpriteComponent>().getX();
        int enemyY = enemyParty[action]->getComponent<bSpriteComponent>().getY();
        uiBoxes[8]->getComponent<bSpriteComponent>().setX(enemyX + 90);
        uiBoxes[8]->getComponent<bSpriteComponent>().setY(enemyY - 10);
        uiBoxes[8]->getComponent<bSpriteComponent>().draw();
    }
    else if (menu == ALLY) {
        int currY = uiBoxes[8]->getComponent<bSpriteComponent>().getY();
        int partyX = uiBoxes[action + 2]->getComponent<bSpriteComponent>().getX();
        int partyY = uiBoxes[action + 2]->getComponent<bSpriteComponent>().getY();
        
        uiBoxes[8]->getComponent<bSpriteComponent>().setX(partyX + 90);
        uiBoxes[8]->getComponent<bSpriteComponent>().setY(partyY - 10);
        uiBoxes[8]->getComponent<bSpriteComponent>().draw();
    }
}