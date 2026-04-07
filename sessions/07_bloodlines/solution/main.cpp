#include "entity.h"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "================================\n";
    std::cout << "  BLOODLINES (INHERITANCE)\n";
    std::cout << "================================\n";

    std::cout << "\nCreating entities...\n";
    Entity rock("Rock", 100);
    std::cout << "✓ Created Entity: " << rock.getName() << "\n";

    Character hero("Hero", 100, 50);
    std::cout << "✓ Created Character: " << hero.getName() << "\n";

    Enemy goblin("Goblin", 50, 25, 10);
    std::cout << "✓ Created Enemy: " << goblin.getName() << "\n";

    std::cout << "\nEntity details:\n";
    rock.display();
    std::cout << "\n";
    hero.display();
    std::cout << "\n";
    goblin.display();

    std::cout << "\nTesting damage...\n";
    rock.takeDamage(30);
    std::cout << "✓ " << rock.getName() << " took 30 damage\n";

    hero.takeDamage(20);
    std::cout << "✓ " << hero.getName() << " took 20 damage\n";

    goblin.takeDamage(40);
    std::cout << "✓ " << goblin.getName() << " took 40 damage\n";

    std::cout << "\nAfter damage:\n";
    rock.display();
    std::cout << "\n";
    hero.display();
    std::cout << "\n";
    goblin.display();

    std::cout << "\nTesting healing...\n";
    rock.heal(20);
    std::cout << "✓ " << rock.getName() << " healed 20 HP\n";

    std::cout << "\nTesting mana usage...\n";
    hero.useMana(20);
    std::cout << "✓ " << hero.getName() << " used 20 mana\n";
    hero.display();

    std::cout << "\nTesting polymorphism...\n";
    std::vector<Entity*> entities = {&rock, &hero, &goblin};

    std::cout << "All entities:\n";
    for (Entity* e : entities) {
        e->display();
        std::cout << "  Alive: " << (e->isAlive() ? "Yes" : "No") << "\n\n";
    }

    return 0;
}
