#include <enemyAI.h>

std::vector<int> getAliveIndices() {
    std::vector<int> aliveIndices;

    // Loop through the party vector
    for (int i = 0; i < playerParty.size(); ++i) {
        // Check if the current party member is alive (has more than 0 HP)
        if (playerParty[i]->getComponent<statsComponent>().HP() > 0) {
            aliveIndices.push_back(i); // Add the index to the list of alive indices
        }
    }

    return aliveIndices;
}

std::unique_ptr<action> enemyAI::aggressiveAction(Entity* enemy) {
    std::vector<int> aliveIndices = getAliveIndices();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, aliveIndices.size() - 1); // Adjusted for zero-based indexing

    // Generate a random index to select the target party member
    int randIndex = dis(gen);
    int targetIndex = aliveIndices[randIndex];

    return std::make_unique<action>(DAMAGE, enemy, ARTS, 0, playerParty[targetIndex]);
}

std::unique_ptr<action> enemyAI::normalAction(Entity* enemy) {
    std::vector<int> aliveIndices = getAliveIndices();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, aliveIndices.size() - 1); // Adjusted for zero-based indexing

    // Generate a random index to select the target party member
    int randIndex = dis(gen);
    int targetIndex = aliveIndices[randIndex];

    return std::make_unique<action>(DAMAGE, enemy, BASH, -1, playerParty[targetIndex]);
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

