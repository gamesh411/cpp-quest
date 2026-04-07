#pragma once
#include <string>
#include <vector>

// ============================================================================
// REQUIRED TYPES AND CLASSES FOR TESTS
// ============================================================================

/**
 * Entity abstract base class - Polymorphic game entity
 *
 * Requirements for tests:
 * - Constructor: Entity(name, maxHealth, attackPower)
 * - Virtual destructor
 * - Const getters: getName(), getHealth(), isAlive()
 * - takeDamage(amount) - health cannot go below 0
 * - Three pure virtual functions: attack(Entity*), defend(), getType() const
 *
 * Hints:
 * - What makes a class abstract? How do you declare functions that
 *   derived classes MUST implement?
 * - Think about which members derived classes need to access
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/abstract_class
 */
class Entity {
   protected:
    // TODO: Add members

   public:
    // TODO: Implement Entity
};

/**
 * Warrior class - Melee combatant with armor
 *
 * Requirements for tests:
 * - Constructor: Warrior(name, health, attackPower, armor)
 * - attack: deals attackPower_ damage to target
 * - defend: prints a message
 * - getType: returns "Warrior"
 * - Getter: getArmor()
 */
class Warrior : public Entity {
   private:
    // TODO: Add members

   public:
    // TODO: Implement Warrior
};

/**
 * Mage class - Spell caster with mana
 *
 * Requirements for tests:
 * - Constructor: Mage(name, health, attackPower, mana)
 * - attack: uses mana to deal damage (check the tests for the exact cost)
 * - defend: prints a message
 * - getType: returns "Mage"
 * - Getter: getMana()
 *
 * Hints:
 * - Read the test cases carefully to understand when attack succeeds or fails
 */
class Mage : public Entity {
   private:
    // TODO: Add members

   public:
    // TODO: Implement Mage
};

/**
 * CombatSystem class - Manages combat between entities
 *
 * Requirements for tests:
 * - addCombatant(Entity*)
 * - executeTurn(attackerIndex, targetIndex)
 * - displayStatus() const
 * - getCombatantCount() const
 *
 * Hints:
 * - How do you store a collection of polymorphic objects?
 */
class CombatSystem {
   private:
    // TODO: Add members

   public:
    // TODO: Implement CombatSystem
};
