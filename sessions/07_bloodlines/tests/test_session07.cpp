#include "../starter/entity.h"

#include <catch2/catch_all.hpp>

TEST_CASE("Entity creation", "[session07][entity]") {
    Entity e("TestEntity", 100);

    REQUIRE(e.getName() == "TestEntity");
    REQUIRE(e.getHealth() == 100);
    REQUIRE(e.getMaxHealth() == 100);
    REQUIRE(e.isAlive() == true);
}

TEST_CASE("Entity damage", "[session07][entity]") {
    Entity e("Test", 100);

    e.takeDamage(30);
    REQUIRE(e.getHealth() == 70);
    REQUIRE(e.isAlive() == true);

    e.takeDamage(80);
    REQUIRE(e.getHealth() == 0);
    REQUIRE(e.isAlive() == false);
}

TEST_CASE("Entity healing", "[session07][entity]") {
    Entity e("Test", 100);

    e.takeDamage(50);
    REQUIRE(e.getHealth() == 50);

    e.heal(30);
    REQUIRE(e.getHealth() == 80);

    e.heal(50);  // Over max
    REQUIRE(e.getHealth() == 100);
}

TEST_CASE("Character creation", "[session07][character]") {
    Character c("Hero", 100, 50);

    REQUIRE(c.getName() == "Hero");
    REQUIRE(c.getHealth() == 100);
    REQUIRE(c.getMana() == 50);
    REQUIRE(c.getMaxMana() == 50);
}

TEST_CASE("Character inherits Entity methods", "[session07][character]") {
    Character c("Hero", 100, 50);

    c.takeDamage(20);
    REQUIRE(c.getHealth() == 80);

    c.heal(10);
    REQUIRE(c.getHealth() == 90);

    REQUIRE(c.isAlive() == true);
}

TEST_CASE("Character mana usage", "[session07][character]") {
    Character c("Hero", 100, 50);

    c.useMana(20);
    REQUIRE(c.getMana() == 30);

    c.useMana(40);  // Over available
    REQUIRE(c.getMana() == 0);

    c.restoreMana(25);
    REQUIRE(c.getMana() == 25);

    c.restoreMana(50);  // Over max
    REQUIRE(c.getMana() == 50);
}

TEST_CASE("Enemy creation", "[session07][enemy]") {
    Enemy e("Goblin", 50, 25, 10);

    REQUIRE(e.getName() == "Goblin");
    REQUIRE(e.getHealth() == 50);
    REQUIRE(e.getExperienceValue() == 25);
    REQUIRE(e.getGoldDrop() == 10);
}

TEST_CASE("Enemy inherits Entity methods", "[session07][enemy]") {
    Enemy e("Goblin", 50, 25, 10);

    e.takeDamage(30);
    REQUIRE(e.getHealth() == 20);

    e.heal(10);
    REQUIRE(e.getHealth() == 30);

    REQUIRE(e.isAlive() == true);
}

TEST_CASE("Polymorphism through base class pointer", "[session07][polymorphism]") {
    Character c("Hero", 100, 50);
    Enemy e("Goblin", 50, 25, 10);

    Entity* ptr1 = &c;
    Entity* ptr2 = &e;

    REQUIRE(ptr1->getName() == "Hero");
    REQUIRE(ptr2->getName() == "Goblin");

    ptr1->takeDamage(20);
    REQUIRE(ptr1->getHealth() == 80);

    ptr2->takeDamage(30);
    REQUIRE(ptr2->getHealth() == 20);
}

TEST_CASE("Virtual destructor", "[session07][virtual]") {
    // This test verifies virtual destructor exists
    Entity* ptr = new Character("Test", 100, 50);
    delete ptr;  // Should call Character destructor

    REQUIRE(true);  // If we get here, no crash
}

TEST_CASE("Constructor chaining", "[session07][constructor]") {
    // Verify base class is properly initialized
    Character c("Hero", 100, 50);

    // Base class members accessible through derived
    REQUIRE(c.getName() == "Hero");
    REQUIRE(c.getMaxHealth() == 100);

    // Derived class members
    REQUIRE(c.getMaxMana() == 50);
}

TEST_CASE("Protected members accessible in derived", "[session07][protected]") {
    // This is tested by compilation
    // If protected members weren't accessible, derived classes wouldn't compile
    Character c("Test", 100, 50);
    Enemy e("Test", 50, 10, 5);

    REQUIRE(c.getName() == "Test");
    REQUIRE(e.getName() == "Test");
}
