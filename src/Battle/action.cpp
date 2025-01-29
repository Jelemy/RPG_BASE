#include <action.h>

action::action(eventType aType, Entity* actioner, commands cmd, int cIndex, Entity* recip) {
    event = aType;
    user = actioner;
	command = cmd;
	commandIndex = cIndex;
	recipient = recip;
}

action::action (eventType type) 
{
    event = type;
    user = nullptr;
    recipient = nullptr;
    move = ""; 
}

eventType action::getType() 
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
    switch (event) {
        case BATTLESTART:
            return "Enemy encountered!";
        case VICTORY:
            return "Enemy bested!";
        case DEFEAT:
            return "The party was defeated..";
        case DAMAGE: {
            string userName = user->getComponent<statsComponent>().nme();
            string recipName = recipient->getComponent<statsComponent>().nme();
            string artName = "";
            if (command != BASH) {
                artName = user->getComponent<statsComponent>().art()[commandIndex];
            }
            int dmg;
            string line1 = "";
            
            switch (command) {
                case BASH:
                    dmg = bManager->performAttack(user, recipient);
                    line1 = userName + " bashed!@";
                    break;      
                case ARTS:
                    dmg = bManager->performArt(user, recipient, commandIndex);
                    if (dmg == -1) {
                        line1 = userName + "'s " + artName + " failed!@";
                        dmg = 0;
                    } else {
                        line1 = userName + " used " + artName + "@";
                    }
                    break;
                default:
                    break;
            }
            string line2 = recipName + " takes " + to_string(dmg) + " damage!";
            return line1 + line2;
        }
        case HEAL: {
            string userName = user->getComponent<statsComponent>().nme();
            string recipName = recipient->getComponent<statsComponent>().nme();
            string artName = user->getComponent<statsComponent>().art()[commandIndex];
            int heal = bManager->performArt(user, recipient, commandIndex);
            string line1 = userName + " used " + artName + "@";
            string line2 = "";
            if (heal >= 0 ) {
                line2 = recipName + " recovers " + to_string(heal) + " health!";
                return line1 + line2;
            }
            else if (heal == -1) {
                line2 = "It failed due to lack of MP!";
            }
            else if (heal == -2) {
                line2 = "Incapicitated allies can't be healed!";
            }
            return line1 + line2;
        }
        default:
            return "";
            break;
    }
}
