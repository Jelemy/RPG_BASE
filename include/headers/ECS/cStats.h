#pragma once

#include "components.h"
#include <vector>
#include <tuple>

typedef std::vector<std::string> arts;

class statsComponent : public Component
{
private:
    string name;
    int maxHealth;
    int currHealth;
    int maxMana;
    int mana;
    int strength;
    int intelligence;
    int speed;
    int dexterity;
    int defense;
    int resistance;
    arts artsList;
    int turns;

public:

    statsComponent(string n, int maxHP, int HP, int maxMP, int mp, int str, int intl, int spd, int dex, int def, int res, arts a)
    {
        name = n;
        maxHealth = maxHP;
        maxMana = maxMP;
        mana = mp;
        currHealth = HP;
        strength = str;
        intelligence = intl;
        speed = spd;
        dexterity = dex;
        defense = def;
        resistance = res;
        artsList = a;
        turns = 1;
    }
    // Getters
    int trns() { return turns; }
    int  maxHP() { return maxHealth; }
    int HP() { return currHealth; }
    int maxMP() { return maxMana; }
    int MP() { return mana; }
    int str() { return strength; }
    int intl() {return intelligence; }
    int spd() {return speed; }
    int dex() { return dexterity; }
    int def() { return defense; }
    int res() {return resistance; }
    string art(int index) { return artsList[index];}
    string nme() { return name; }
    


    // Setters
    void setMaxHP(int maxHP) { maxHealth = maxHP; }
    void setHP(int HP) { currHealth = HP; }
    void setMaxMP(int maxMP) { maxMana = maxMP; }
    void setMP(int MP) { mana = MP; }
    void setStr(int str) { strength = str; }
    void setIntl(int intl) { intelligence = intl; }
    void setSpd(int spd) { speed = spd; }
    void setDex(int dex) { dexterity = dex; }
    void setRes(int res) { resistance = res; }
    void setTurns(int t) { turns = t; }


    
};