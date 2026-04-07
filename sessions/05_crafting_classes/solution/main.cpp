#include "spell.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "  CRAFTING CLASSES\n";
    std::cout << "================================\n";

    std::cout << "\nCreating spells...\n";
    Spell fireball("Fireball", 50, 100, SpellType::DAMAGE);
    Spell heal("Heal", 30, 50, SpellType::HEALING);
    Spell shield("Shield", 40, 75, SpellType::BUFF);

    std::cout << "✓ Created: " << fireball.getName() << " (Cost: " << fireball.getManaCost()
              << ", Power: " << fireball.getPower() << ")\n";
    std::cout << "✓ Created: " << heal.getName() << " (Cost: " << heal.getManaCost()
              << ", Power: " << heal.getPower() << ")\n";
    std::cout << "✓ Created: " << shield.getName() << " (Cost: " << shield.getManaCost()
              << ", Power: " << shield.getPower() << ")\n";

    std::cout << "\nAdding to spellbook (max 5)...\n";
    SpellBook book(5);

    if (book.addSpell(fireball)) {
        std::cout << "✓ Added " << fireball.getName() << "\n";
    }
    if (book.addSpell(heal)) {
        std::cout << "✓ Added " << heal.getName() << "\n";
    }
    if (book.addSpell(shield)) {
        std::cout << "✓ Added " << shield.getName() << "\n";
    }

    book.listSpells();

    std::cout << "\nCasting spells...\n";
    int mana = 100;

    const Spell* found = book.findSpell("Fireball");
    if (found && found->canCast(mana)) {
        int damage = const_cast<Spell*>(found)->cast();
        std::cout << "✓ Cast " << found->getName() << " for " << damage << " damage!\n";
        mana -= found->getManaCost();
    }

    found = book.findSpell("Heal");
    if (found && found->canCast(mana)) {
        int healing = const_cast<Spell*>(found)->cast();
        std::cout << "✓ Cast " << found->getName() << " for " << healing << " healing!\n";
        mana -= found->getManaCost();
    }

    std::cout << "\nRemaining mana: " << mana << "\n";

    return 0;
}
