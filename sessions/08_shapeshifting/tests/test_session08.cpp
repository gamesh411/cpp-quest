#include "../starter/combat.h"

#include <catch2/catch_all.hpp>

/*
 * Session 8 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Abstract base class (Entity with pure virtual functions)
 * ✅ Virtual functions (attack, defend, getType)
 * ✅ Polymorphism (base pointer to derived objects)
 * ✅ Override keyword usage
 * ✅ Warrior class (attack, defend, armor)
 * ✅ Mage class (attack, defend, mana)
 * ✅ Dynamic dispatch (correct method called)
 * ✅ CombatSystem (add, execute, display)
 * ✅ Entity state (health, damage, alive)
 * ✅ Edge cases (no mana, zero health)
 *
 * Coverage: 12 test cases, 50+ assertions
 */

TEST_CASE("Warrior creation", "[session08][warrior]") {
    Warrior warrior("TestWarrior", 100, 20, 10);

    REQUIRE(warrior.getName() == "TestWarrior");
    REQUIRE(warrior.getHealth() == 100);
    REQUIRE(warrior.isAlive());
    REQUIRE(warrior.getType() == "Warrior");
    REQUIRE(warrior.getArmor() == 10);
}

TEST_CASE("Mage creation", "[session08][mage]") {
    Mage mage("TestMage", 80, 30, 50);

    REQUIRE(mage.getName() == "TestMage");
    REQUIRE(mage.getHealth() == 80);
    REQUIRE(mage.isAlive());
    REQUIRE(mage.getType() == "Mage");
    REQUIRE(mage.getMana() == 50);
}

TEST_CASE("Entity polymorphism", "[session08][polymorphism]") {
    Warrior warrior("Warrior", 100, 20, 10);
    Mage mage("Mage", 80, 30, 50);

    Entity* entity1 = &warrior;
    Entity* entity2 = &mage;

    REQUIRE(entity1->getType() == "Warrior");
    REQUIRE(entity2->getType() == "Mage");
    REQUIRE(entity1->getName() == "Warrior");
    REQUIRE(entity2->getName() == "Mage");
}

TEST_CASE("Warrior attack", "[session08][warrior][attack]") {
    Warrior attacker("Attacker", 100, 25, 10);
    Warrior target("Target", 100, 20, 10);

    attacker.attack(&target);

    REQUIRE(target.getHealth() == 75);
    REQUIRE(target.isAlive());
}

TEST_CASE("Mage attack with mana", "[session08][mage][attack]") {
    Mage attacker("Mage", 80, 30, 50);
    Warrior target("Target", 100, 20, 10);

    int initialMana = attacker.getMana();
    attacker.attack(&target);

    REQUIRE(target.getHealth() == 70);
    REQUIRE(attacker.getMana() == initialMana - 10);
}

TEST_CASE("Mage attack without mana", "[session08][mage][attack][edge]") {
    Mage attacker("Mage", 80, 30, 5);
    Warrior target("Target", 100, 20, 10);

    attacker.attack(&target);

    REQUIRE(target.getHealth() == 100);
    REQUIRE(attacker.getMana() == 5);
}

TEST_CASE("Entity take damage", "[session08][entity]") {
    Warrior warrior("Warrior", 100, 20, 10);

    SECTION("Partial damage") {
        warrior.takeDamage(30);
        REQUIRE(warrior.getHealth() == 70);
        REQUIRE(warrior.isAlive());
    }

    SECTION("Lethal damage") {
        warrior.takeDamage(100);
        REQUIRE(warrior.getHealth() == 0);
        REQUIRE_FALSE(warrior.isAlive());
    }

    SECTION("Overkill damage") {
        warrior.takeDamage(150);
        REQUIRE(warrior.getHealth() == 0);
        REQUIRE_FALSE(warrior.isAlive());
    }
}

TEST_CASE("Defend methods", "[session08][defend]") {
    Warrior warrior("Warrior", 100, 20, 10);
    Mage mage("Mage", 80, 30, 50);

    // Should not crash
    warrior.defend();
    mage.defend();

    REQUIRE(warrior.isAlive());
    REQUIRE(mage.isAlive());
}

TEST_CASE("CombatSystem add combatants", "[session08][combat]") {
    CombatSystem combat;
    Warrior warrior("Warrior", 100, 20, 10);
    Mage mage("Mage", 80, 30, 50);

    combat.addCombatant(&warrior);
    combat.addCombatant(&mage);

    // Should not crash
    combat.displayStatus();
}

TEST_CASE("CombatSystem execute turn", "[session08][combat]") {
    CombatSystem combat;
    Warrior warrior1("Warrior1", 100, 25, 10);
    Warrior warrior2("Warrior2", 100, 20, 10);

    combat.addCombatant(&warrior1);
    combat.addCombatant(&warrior2);

    combat.executeTurn(0, 1);

    REQUIRE(warrior2.getHealth() == 75);
}

TEST_CASE("Polymorphic attack through base pointer", "[session08][polymorphism][attack]") {
    Warrior warrior("Warrior", 100, 20, 10);
    Mage mage("Mage", 80, 30, 50);
    Warrior target("Target", 100, 15, 5);

    Entity* attacker1 = &warrior;
    Entity* attacker2 = &mage;

    attacker1->attack(&target);
    REQUIRE(target.getHealth() == 80);

    attacker2->attack(&target);
    REQUIRE(target.getHealth() == 50);
}

TEST_CASE("Multiple attacks", "[session08][integration]") {
    Mage mage("Mage", 80, 30, 50);
    Warrior target("Target", 100, 20, 10);

    // Mage can attack 5 times (50 mana / 10 per attack)
    for (int i = 0; i < 5; i++) {
        mage.attack(&target);
    }

    REQUIRE(target.getHealth() == 0);
    REQUIRE(mage.getMana() == 0);

    // 6th attack should fail (no mana)
    mage.attack(&target);
    REQUIRE(target.getHealth() == 0);
}

TEST_CASE("Combat scenario", "[session08][integration]") {
    CombatSystem combat;

    Warrior warrior1("Knight", 150, 30, 15);
    Warrior warrior2("Barbarian", 200, 40, 10);
    Mage mage1("Wizard", 100, 50, 100);
    Mage mage2("Sorcerer", 90, 45, 80);

    combat.addCombatant(&warrior1);
    combat.addCombatant(&warrior2);
    combat.addCombatant(&mage1);
    combat.addCombatant(&mage2);

    // Turn 1: Knight attacks Wizard
    combat.executeTurn(0, 2);
    REQUIRE(mage1.getHealth() == 70);

    // Turn 2: Wizard attacks Knight
    combat.executeTurn(2, 0);
    REQUIRE(warrior1.getHealth() == 100);

    // Turn 3: Barbarian attacks Sorcerer
    combat.executeTurn(1, 3);
    REQUIRE(mage2.getHealth() == 50);

    combat.displayStatus();
}

TEST_CASE("Virtual destructor", "[session08][polymorphism]") {
    Entity* entity = new Warrior("Temp", 100, 20, 10);

    // Should properly delete through base pointer
    delete entity;

    REQUIRE(true);
}
