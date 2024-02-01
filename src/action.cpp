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
        case DAMAGE: {
            printf("ciyayay");
            std::cout << commandIndex << std::endl;
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
                    printf("hiyayay");
                    dmg = bManager->performAttack(user, recipient);
                    line1 = userName + " bashed!@";
                    //printf("enemybahs\n");
                    //std::cout << enemyParty[1]->getComponent<statsComponent>().HP() << std::endl;
                    break;      
                case ARTS:
                    printf("diyayay");
                    dmg = bManager->performArt(user, recipient, commandIndex);
                    line1 = userName + " used " + artName + "@";
                    //printf("enemyart\n");
                    //std::cout << enemyParty[1]->getComponent<statsComponent>().HP() << std::endl;
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
            
            string line2 = recipName + " recovers " + to_string(heal) + " health!";
            return line1 + line2;
        }
        default:
            return "";
            break;
    }
    printf("enemy");
    std::cout << enemyParty[0]->getComponent<statsComponent>().HP() << std::endl;


}
