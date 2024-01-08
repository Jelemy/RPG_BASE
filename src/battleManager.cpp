#include <battleManager.h>


battleManager::battleManager(entities &playerP, entities &enemyP)
{
    playerParty = playerP;
    enemyParty = enemyP;
    partyTurn = false;
    entityTurn = nullptr;
    artInfo art1 = make_tuple("magic_damage", 3, 10, "Deals fire magic damage");
    artInfo art2 = make_tuple("physical_damage", 5, 10, "Deals light damage");
    artInfo art3 = make_tuple("heal", 5, 40, "Restores 40 HP");
    artsInfo.insert({{"Fire", art1},{"Mega Bash", art2}, {"Heal", art3}});
}
Entity* battleManager::getTurn()
{
    int maxSpeed = 0;
    int maxSpeedIndex = -1;
    // true if player party turn, false if enemy party turn

    for (int i = 0; i < playerParty.size(); i++) {
        if (playerParty[i]->getComponent<statsComponent>().spd() > maxSpeed &&
            playerParty[i]->getComponent<statsComponent>().trns() > 0 &&
            playerParty[i]->getComponent<statsComponent>().HP() > 0) {

            maxSpeed = playerParty[i]->getComponent<statsComponent>().spd();
            maxSpeedIndex = i;
            partyTurn = true;
        }
    }
    for (int i = 0; i < enemyParty.size(); i++) {
        if (enemyParty[i]->getComponent<statsComponent>().spd() > maxSpeed &&
            enemyParty[i]->getComponent<statsComponent>().trns() > 0 &&
            enemyParty[i]->getComponent<statsComponent>().HP() > 0) {

            maxSpeed = enemyParty[i]->getComponent<statsComponent>().spd();
            maxSpeedIndex = i;
            partyTurn = false;
        }
    }
    // return entity with the highest speed
    if (maxSpeedIndex > -1 ) {
        if (partyTurn) {
            entityTurn = playerParty[maxSpeedIndex];
            return playerParty[maxSpeedIndex];
        }
        else {
            entityTurn = enemyParty[maxSpeedIndex];
            return enemyParty[maxSpeedIndex];       
        }
    }
    // Round ends and everyone's turn capacity is reset to 1
    else {
        for (int i = 0; i < playerParty.size(); i++) {
            playerParty[i]->getComponent<statsComponent>().setTurns(1);
        }
        for (int i = 0; i < enemyParty.size(); i++) {
            enemyParty[i]->getComponent<statsComponent>().setTurns(1);
        }
        entityTurn = nullptr;
        return NULL;
    }
}

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
void battleManager::performAttack(int recipientIndex)
{
    int dmg;
    int currHP;
    entityTurn->getComponent<statsComponent>().setTurns(0);
    if (partyTurn) {
        dmg = entityTurn->getComponent<statsComponent>().str()/2 - enemyParty[recipientIndex]->getComponent<statsComponent>().def()/4;
        currHP = enemyParty[recipientIndex]->getComponent<statsComponent>().HP();
        if (currHP - dmg < 0) {
            enemyParty[recipientIndex]->getComponent<statsComponent>().setHP(0);
        }
        else {
            enemyParty[recipientIndex]->getComponent<statsComponent>().setHP(currHP - dmg);
        }
    }
    else {
        dmg = entityTurn->getComponent<statsComponent>().str()/2 - playerParty[recipientIndex]->getComponent<statsComponent>().def()/4;
        currHP = playerParty[recipientIndex]->getComponent<statsComponent>().HP();
        if (currHP - dmg < 0) {
            playerParty[recipientIndex]->getComponent<statsComponent>().setHP(0);
        }
        else {
            playerParty[recipientIndex]->getComponent<statsComponent>().setHP(currHP - dmg);
        } 
    }
}
void battleManager::performPhysical(string artName, Entity* recipient) {
    // Check if user has enough HP to perform physical art
    int userHP = entityTurn->getComponent<statsComponent>().HP();
    if (userHP < get<1>(artsInfo[artName])){
        return;
    }
    entityTurn->getComponent<statsComponent>().setHP(userHP - get<1>(artsInfo[artName]));
    entityTurn->getComponent<statsComponent>().setTurns(0);

    // Reduce recipient HP
    int str = entityTurn->getComponent<statsComponent>().str();
    int artDmg = get<2>(artsInfo[artName]);
    int recipientRes = recipient->getComponent<statsComponent>().res();
    int recipientHP = recipient->getComponent<statsComponent>().HP();

    int dmg = (str + artDmg)/2 - recipientRes/4;
    recipient->getComponent<statsComponent>().setHP(recipientHP - dmg);
}
void battleManager::performMagic(string artName, Entity* recipient) {
    // Check if user has enough mp and reduce user MP
    int userMP = entityTurn->getComponent<statsComponent>().MP();
    if (userMP < get<1>(artsInfo[artName])){
        return;
    }
    entityTurn->getComponent<statsComponent>().setMP(userMP - get<1>(artsInfo[artName]));
    entityTurn->getComponent<statsComponent>().setTurns(0);

    // Reduce recipient HP
    int intl = entityTurn->getComponent<statsComponent>().intl();
    int artDmg = get<2>(artsInfo[artName]);
    int recipientRes = recipient->getComponent<statsComponent>().res();
    int recipientHP = recipient->getComponent<statsComponent>().HP();

    int dmg = (intl + artDmg)/2 - recipientRes/4;
    recipient->getComponent<statsComponent>().setHP(recipientHP - dmg);
}

void battleManager::performHeal(string artName, Entity* recipient) {
    int userMP = entityTurn->getComponent<statsComponent>().MP();
    if (userMP < get<1>(artsInfo[artName])){
        return;
    }
    entityTurn->getComponent<statsComponent>().setMP(userMP - get<1>(artsInfo[artName]));
    entityTurn->getComponent<statsComponent>().setTurns(0);

    int healAmount = get<2>(artsInfo[artName]);
    int rHP = recipient->getComponent<statsComponent>().HP();
    int rMaxHP = recipient->getComponent<statsComponent>().maxHP();
    if (rHP + healAmount > rMaxHP) {
        recipient->getComponent<statsComponent>().setHP(rMaxHP);
    }
    else {
        recipient->getComponent<statsComponent>().setHP(rHP + healAmount);
    }
}

void battleManager::performArt(int artIndex, int recipientIndex)
{
    string artName = entityTurn->getComponent<statsComponent>().art(artIndex);
    string artType = get<0>(artsInfo[artName]);
    if (partyTurn) {
        if (artType == "magic_damage") {
            performMagic(artName, enemyParty[recipientIndex]);
        }
        else if (artType == "physical_damage") {
            performPhysical(artName, enemyParty[recipientIndex]);
        }
        else {
            performHeal(artName, playerParty[recipientIndex]);
        }
    }
    else {
        if (artType == "magic_damage") {
            performMagic(artName, playerParty[recipientIndex]);
        }
        else if (artType == "physical_damage") {
            performPhysical(artName, playerParty[recipientIndex]);
        }
        else {
            performHeal(artName, enemyParty[recipientIndex]);
        }
    }
}