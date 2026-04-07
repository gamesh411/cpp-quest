#include "combat.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "  SHAPESHIFTING (POLYMORPHISM)\n";
    std::cout << "================================\n";

    std::cout << "\nCreating combatants...\n";
    Warrior conan("Conan", 150, 30, 50);
    std::cout << "✓ Created Warrior: " << conan.getName() << "\n";

    Mage gandalf("Gandalf", 80, 40, 100);
    std::cout << "✓ Created Mage: " << gandalf.getName() << "\n";

    CombatSystem combat;
    combat.addCombatant(&conan);
    combat.addCombatant(&gandalf);

    combat.displayStatus();

    std::cout << "\n--- Combat Begins ---\n";

    combat.executeTurn(0, 1);  // Conan attacks Gandalf
    combat.executeTurn(1, 0);  // Gandalf attacks Conan

    combat.displayStatus();

    std::cout << "\n--- Demonstrating Polymorphism ---\n";
    Entity* entities[] = {&conan, &gandalf};

    std::cout << "\nCalling virtual functions through base pointer:\n";
    for (int i = 0; i < 2; ++i) {
        std::cout << "\n" << entities[i]->getType() << ": " << entities[i]->getName() << "\n";
        entities[i]->defend();
    }

    std::cout << "\n--- Combat Complete ---\n";
    std::cout << "Final survivors:\n";
    for (int i = 0; i < 2; ++i) {
        if (entities[i]->isAlive()) {
            std::cout << "  ✓ " << entities[i]->getName() << " (HP: " << entities[i]->getHealth()
                      << ")\n";
        }
    }

    return 0;
}
