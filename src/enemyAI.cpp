#include <enemyAI.h>

std::unique_ptr<action> enemyAI::aggressiveAction(Entity* enemy) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Generate a random probability value
    double probability = dis(gen);
    double targetThreshold = 0.5;

    if (probability < targetThreshold) {
        return std::make_unique<action>(DAMAGE, enemy, ARTS, 0, playerParty[0]);
    } else {
        return std::make_unique<action>(DAMAGE, enemy, ARTS, 0, playerParty[1]);
    }
}

std::unique_ptr<action> enemyAI::normalAction(Entity* enemy) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Generate a random probability value
    double probability = dis(gen);
    double targetThreshold = 0.5;

    if (probability < targetThreshold) {
        return std::make_unique<action>(DAMAGE, enemy, BASH, -1, playerParty[0]);
    } else {
        return std::make_unique<action>(DAMAGE, enemy, BASH, -1, playerParty[1]);
    }
}

std::unique_ptr<action> enemyAI::generateAction(Entity* enemy) {
    // extendable design: threshold behaviours determined by data driven json design
    int maxHP = enemy->getComponent<statsComponent>().maxHP();
    int HP = enemy->getComponent<statsComponent>().HP();
    double healthPercent = HP/maxHP;

    if (healthPercent < 0.3) {
        // If health is less than 30%, take aggressive action
        return aggressiveAction(enemy);
    } else {
        // Otherwise, take normal action
        return normalAction(enemy);
    }

}

