#pragma once
#include <string>
#include <vector>

// ============================================================================
// REQUIRED TYPES AND CLASSES FOR TESTS
// ============================================================================

/**
 * Interface: Combatant
 * - Pure virtual: attack(), getAttackPower() const
 * - Virtual destructor
 */
// TODO: Define Combatant interface

/**
 * Interface: Trader
 * - Pure virtual: trade(), getGold() const
 * - Virtual destructor
 */
// TODO: Define Trader interface

/**
 * Interface: QuestGiver
 * - Pure virtual: giveQuest(), getQuestName() const
 * - Virtual destructor
 */
// TODO: Define QuestGiver interface

/**
 * Entity base class
 *
 * Requirements for tests:
 * - Constructor: Entity(name)
 * - Virtual destructor
 * - Const getter: getName()
 *
 * Hints:
 * - This class is inherited by classes that also inherit from the
 *   interfaces above. Think about what problem arises when a class
 *   inherits the same base through multiple paths, and how to solve it.
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/derived_class
 * - https://isocpp.org/wiki/faq/multiple-inheritance
 */
// TODO: Define Entity base class

/**
 * Merchant class - Inherits from Entity, Combatant, and Trader
 *
 * Requirements for tests:
 * - Constructor: Merchant(name, attackPower, gold)
 * - Implements all Combatant and Trader methods
 * - Can be used through Entity*, Combatant*, or Trader* pointers
 */
// TODO: Define Merchant class

/**
 * QuestMaster class - Inherits from Entity, QuestGiver, and Trader
 *
 * Requirements for tests:
 * - Constructor: QuestMaster(name, questName, gold)
 * - Implements all QuestGiver and Trader methods
 * - Can be used through Entity*, QuestGiver*, or Trader* pointers
 */
// TODO: Define QuestMaster class

/**
 * NPCManager class - Manages a collection of NPCs
 *
 * Requirements for tests:
 * - addNPC(Entity*)
 * - findNPC(name) - two overloads needed (think about const correctness)
 * - getNPCCount() const
 *
 * Hints:
 * - What should findNPC return when called on a const vs non-const manager?
 */
// TODO: Define NPCManager class
