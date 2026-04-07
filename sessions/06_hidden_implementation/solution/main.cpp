#include "game_engine.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "  HIDDEN IMPLEMENTATION\n";
    std::cout << "================================\n";

    std::cout << "\nCreating game engine...\n";
    GameEngine engine;
    std::cout << "✓ Engine created\n";

    std::cout << "\nAdding entities...\n";
    engine.addPlayer("Hero", 100);
    std::cout << "✓ Added player: Hero\n";

    engine.addPlayer("Mage", 80);
    std::cout << "✓ Added player: Mage\n";

    engine.addEnemy("Goblin", 50);
    std::cout << "✓ Added enemy: Goblin\n";

    engine.addEnemy("Orc", 75);
    std::cout << "✓ Added enemy: Orc\n";

    engine.displayStatus();

    std::cout << "\nUpdating game...\n";
    engine.update();
    std::cout << "✓ Turn 1 complete\n";

    engine.displayStatus();

    std::cout << "\nTesting move semantics...\n";
    GameEngine engine2 = std::move(engine);
    std::cout << "✓ Engine moved successfully\n";
    std::cout << "✓ New engine has " << engine2.getPlayerCount() << " players\n";

    return 0;
}
