#include <battleManager.h>


battleManager::battleManager()
{}


string battleManager::checkOutcome() 
{
    int playerAlive = 0;
    int enemyAlive = 0;
    // Check amount of player party members still alive
    for (int i = 0; i < playerParty.size(); i++) {
        if (playerParty[i]->getComponent<statsComponent>().HP() > 0) {
            playerAlive++;
                
        }   
    }
    // Check amount of enemies still alive
    for (int i = 0; i < enemyParty.size(); i++) {
        if (enemyParty[i]->getComponent<statsComponent>().HP() > 0) {
            enemyAlive++;
                
        }   
    }
    // If no playar party members are left alive then outcome is defeat
    if (playerAlive == 0) {
        return "defeat";
    }
    // If no enemies are left alive then outcome is victory
    else if (enemyAlive == 0) {
        return "victory";
    }
    else {
        return "continue";
    }
}
//{}

// return battle message
int battleManager::performAttack(Entity* actioner, Entity* recipient)
{
    
    int dmg = 0;
    int currHP = 0;
    dmg = actioner->getComponent<statsComponent>().str()/2 - recipient->getComponent<statsComponent>().def()/4;
    currHP = recipient->getComponent<statsComponent>().HP();
    if (currHP - dmg < 0) {
        recipient->getComponent<statsComponent>().setHP(0);
    }
    else {
        recipient->getComponent<statsComponent>().setHP(currHP - dmg);
    }
    return dmg;
    
}
int battleManager::performPhysical(Entity* actioner, string art, Entity* recipient) {
    // Check if user has enough HP to perform physical art
    
    int userHP = actioner->getComponent<statsComponent>().HP();
    if (userHP < get<1>(artsInfo[art])){
        return -1;
    }
    actioner->getComponent<statsComponent>().setHP(userHP - get<1>(artsInfo[art]));

    // Reduce recipient HP
    int str = actioner->getComponent<statsComponent>().str();
    int artDmg = get<2>(artsInfo[art]);
    int recipientDef = recipient->getComponent<statsComponent>().def();
    int recipientHP = recipient->getComponent<statsComponent>().HP();

    int dmg = (str + artDmg)/2 - recipientDef/4;
    recipient->getComponent<statsComponent>().setHP(recipientHP - dmg);
    return dmg;
    
}
int battleManager::performMagic(Entity* actioner, string art, Entity* recipient) {
    
    // Check if user has enough mp and reduce user MP
    int userMP = actioner->getComponent<statsComponent>().MP();
    if (userMP < get<1>(artsInfo[art])){
        return -1;
    }
    actioner->getComponent<statsComponent>().setMP(userMP - get<1>(artsInfo[art]));

    // Reduce recipient HP
    int mag = actioner->getComponent<statsComponent>().intl();
    int artDmg = get<2>(artsInfo[art]);
    int recipientRes = recipient->getComponent<statsComponent>().res();
    int recipientHP = recipient->getComponent<statsComponent>().HP();

    int dmg = (mag + artDmg)/2 - recipientRes/4;
    recipient->getComponent<statsComponent>().setHP(recipientHP - dmg);
    return dmg;
    
}

int battleManager::performHeal(Entity* actioner, string art, Entity* recipient) {
    
    int userMP = actioner->getComponent<statsComponent>().MP();
    if (userMP < get<1>(artsInfo[art])){
        return -1;
    }
    actioner->getComponent<statsComponent>().setMP(userMP - get<1>(artsInfo[art]));
    

    int healAmount = get<2>(artsInfo[art]);
    int rHP = recipient->getComponent<statsComponent>().HP();
    int rMaxHP = recipient->getComponent<statsComponent>().maxHP();
    if (rHP + healAmount > rMaxHP) {
        recipient->getComponent<statsComponent>().setHP(rMaxHP);
    }
    else {
        recipient->getComponent<statsComponent>().setHP(rHP + healAmount);
    }
    return healAmount;
    
}

int battleManager::performArt(Entity* actioner, Entity* recipient, int artIndex)
{
    
    string artName = actioner->getComponent<statsComponent>().art()[artIndex];
    string artType = get<0>(artsInfo[artName]);

    if (artType == "magic_damage") {
        return performMagic(actioner, artName, recipient);
    }
    else if (artType == "physical_damage") {
        return performPhysical(actioner, artName, recipient);
    }
    else {
        return performHeal(actioner, artName, recipient);
    }
    
    
}