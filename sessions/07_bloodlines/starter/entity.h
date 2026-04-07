#pragma once
#include <string>

// ============================================================================
// REQUIRED TYPES AND CLASSES FOR TESTS
// ============================================================================

/**
 * Entity base class - Represents any game entity
 *
 * Requirements for tests:
 * - Constructor: Entity(name, maxHealth) - health starts at maxHealth
 * - Virtual destructor
 * - Const getters: getName(), getHealth(), getMaxHealth()
 * - takeDamage(amount) - health cannot go below 0
 * - heal(amount) - health cannot exceed maxHealth
 * - isAlive() const
 * - virtual display() const
 *
 * Hints:
 * - Think about which access specifier lets derived classes use your members
 * - Why does the destructor need to be virtual?
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/derived_class
 * - https://en.cppreference.com/w/cpp/language/access
 */
class Entity {
   protected:
    // TODO: Add members

   public:
    // TODO: Implement Entity
};

/**
 * Character class - Inherits from Entity, adds mana system
 *
 * Requirements for tests:
 * - Constructor: Character(name, maxHealth, maxMana)
 * - Const getters: getMana(), getMaxMana()
 * - useMana(amount) - mana cannot go below 0
 * - restoreMana(amount) - mana cannot exceed maxMana
 * - Override display()
 *
 * Hints:
 * - How do you pass arguments to the base class constructor?
 * - Look up "constructor chaining" or "member initializer list"
 */
class Character : public Entity {
   private:
    // TODO: Add members

   public:
    // TODO: Implement Character
};

/**
 * Enemy class - Inherits from Entity, adds loot info
 *
 * Requirements for tests:
 * - Constructor: Enemy(name, maxHealth, xp, gold)
 * - Const getters: getExperienceValue(), getGoldDrop()
 * - Override display()
 */
class Enemy : public Entity {
   private:
    // TODO: Add members

   public:
    // TODO: Implement Enemy
};
