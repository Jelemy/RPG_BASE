#include <action.h>

action::action (actionType type, Entity* usr, Entity* recip, string mv){
    aType = type;
    user = usr;
    recipient = recip;
    move = mv;
}

action::action (actionType type) 
{
    aType = type;
    user = nullptr;
    recipient = nullptr;
    move = ""; 
}

actionType action::getType() 
{
    return aType;
}
Entity* action::getUser() 
{
    return user;
}
Entity* action::getRecipient() 
{
    return recipient;
}

string action::getMove()
{
    return move;
}
string action::enact()
{
    if (aType == BATTLESTART) {
        return "Enemy encountered!";
    }
    else if (aType == VICTORY) {
        return "Enemy bested!";
    }
    else if (aType == ACTION) {
        string rName = recipient->getComponent<statsComponent>().nme();
        string uName = user->getComponent<statsComponent>().nme();
        if (move == "bash") {
            return uName + " bashed " + rName;
        }
        else {
            return uName + " used " + move + " on " + rName;
        }
    }
    else if (aType == DAMAGE) {
        string rName = recipient->getComponent<statsComponent>().nme();
        int dmg = 0;
        return rName + " took " + (to_string(dmg)) + " points of damage.";
    }
    else if (aType == HEAL) {
        string rName = recipient->getComponent<statsComponent>().nme();
        int heal = 0;
        return rName + " recovered " + (to_string(heal)) + " health points";
    }
    else {
        return "Battle was lost!";
    }
}
