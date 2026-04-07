#include "npc.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "  ANCIENT POWERS\n";
    std::cout << "================================\n";

    std::cout << "\nCreating NPCs...\n";
    Merchant bob("Bob", 20, 100);
    std::cout << "✓ Created Merchant: " << bob.getName() << "\n";

    QuestMaster sage("Sage", "Find the Artifact", 50);
    std::cout << "✓ Created QuestMaster: " << sage.getName() << "\n";

    std::cout << "\nTesting multiple inheritance...\n";
    std::cout << bob.getName() << " can attack: Power " << bob.getAttackPower() << "\n";
    std::cout << bob.getName() << " can trade: Gold " << bob.getGold() << "\n";

    std::cout << "\n" << sage.getName() << " can give quests: " << sage.getQuestName() << "\n";
    std::cout << sage.getName() << " can trade: Gold " << sage.getGold() << "\n";

    std::cout << "\nTesting polymorphism through interfaces...\n";
    Combatant* c = &bob;
    std::cout << "Combatant: ";
    c->attack();

    Trader* t1 = &bob;
    std::cout << "Trader: ";
    t1->trade();

    QuestGiver* q = &sage;
    std::cout << "\nQuestGiver: ";
    q->giveQuest();

    Trader* t2 = &sage;
    std::cout << "Trader: ";
    t2->trade();

    std::cout << "\nCreating NPC Manager...\n";
    NPCManager manager;
    manager.addNPC(&bob);
    manager.addNPC(&sage);
    std::cout << "✓ Added " << manager.getNPCCount() << " NPCs\n";

    std::cout << "\nTesting const overloading...\n";
    Entity* found1 = manager.findNPC("Bob");
    if (found1) {
        std::cout << "✓ Found NPC (non-const): " << found1->getName() << "\n";
    }

    const NPCManager& constManager = manager;
    const Entity* found2 = constManager.findNPC("Sage");
    if (found2) {
        std::cout << "✓ Found NPC (const): " << found2->getName() << "\n";
    }

    std::cout << "\n--- Demonstrating Virtual Inheritance ---\n";
    std::cout << "Both Merchant and QuestMaster inherit from Entity\n";
    std::cout << "Virtual inheritance ensures single Entity instance\n";
    std::cout << "No diamond problem! ✓\n";

    return 0;
}
