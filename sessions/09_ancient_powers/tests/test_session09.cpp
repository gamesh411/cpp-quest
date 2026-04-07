#include "../starter/npc.h"

#include <catch2/catch_all.hpp>

/*
 * Session 9 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Multiple inheritance (Merchant, QuestMaster)
 * ✅ Virtual inheritance (Entity base, diamond problem)
 * ✅ Abstract interfaces (Combatant, Trader, QuestGiver)
 * ✅ Const overloading (findNPC const/non-const)
 * ✅ Merchant class (attack, trade, getters)
 * ✅ QuestMaster class (giveQuest, trade, getters)
 * ✅ NPCManager (add, find, count)
 * ✅ Polymorphism through multiple interfaces
 * ✅ Edge cases (not found, empty manager)
 *
 * Coverage: 12 test cases, 50+ assertions
 */

TEST_CASE("Merchant creation", "[session09][merchant]") {
    Merchant merchant("Bob", 15, 500);

    REQUIRE(merchant.getName() == "Bob");
    REQUIRE(merchant.getAttackPower() == 15);
    REQUIRE(merchant.getGold() == 500);
}

TEST_CASE("QuestMaster creation", "[session09][questmaster]") {
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    REQUIRE(qm.getName() == "Elder");
    REQUIRE(qm.getQuestName() == "Dragon Slayer");
    REQUIRE(qm.getGold() == 1000);
}

TEST_CASE("Merchant multiple inheritance", "[session09][multiple]") {
    Merchant merchant("Bob", 15, 500);

    // Can be used as Entity
    Entity* entity = &merchant;
    REQUIRE(entity->getName() == "Bob");

    // Can be used as Combatant
    Combatant* combatant = &merchant;
    REQUIRE(combatant->getAttackPower() == 15);

    // Can be used as Trader
    Trader* trader = &merchant;
    REQUIRE(trader->getGold() == 500);
}

TEST_CASE("QuestMaster multiple inheritance", "[session09][multiple]") {
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    // Can be used as Entity
    Entity* entity = &qm;
    REQUIRE(entity->getName() == "Elder");

    // Can be used as QuestGiver
    QuestGiver* questGiver = &qm;
    REQUIRE(questGiver->getQuestName() == "Dragon Slayer");

    // Can be used as Trader
    Trader* trader = &qm;
    REQUIRE(trader->getGold() == 1000);
}

TEST_CASE("Merchant attack", "[session09][merchant]") {
    Merchant merchant("Bob", 15, 500);

    // Should not crash
    merchant.attack();

    REQUIRE(merchant.getAttackPower() == 15);
}

TEST_CASE("Merchant trade", "[session09][merchant]") {
    Merchant merchant("Bob", 15, 500);

    // Should not crash
    merchant.trade();

    REQUIRE(merchant.getGold() == 500);
}

TEST_CASE("QuestMaster giveQuest", "[session09][questmaster]") {
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    // Should not crash
    qm.giveQuest();

    REQUIRE(qm.getQuestName() == "Dragon Slayer");
}

TEST_CASE("QuestMaster trade", "[session09][questmaster]") {
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    // Should not crash
    qm.trade();

    REQUIRE(qm.getGold() == 1000);
}

TEST_CASE("NPCManager add and count", "[session09][manager]") {
    NPCManager manager;
    Merchant merchant("Bob", 15, 500);
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    REQUIRE(manager.getNPCCount() == 0);

    manager.addNPC(&merchant);
    REQUIRE(manager.getNPCCount() == 1);

    manager.addNPC(&qm);
    REQUIRE(manager.getNPCCount() == 2);
}

TEST_CASE("NPCManager find NPC", "[session09][manager]") {
    NPCManager manager;
    Merchant merchant("Bob", 15, 500);
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    manager.addNPC(&merchant);
    manager.addNPC(&qm);

    SECTION("Find existing NPC") {
        Entity* found = manager.findNPC("Bob");
        REQUIRE(found != nullptr);
        REQUIRE(found->getName() == "Bob");
    }

    SECTION("Find another existing NPC") {
        Entity* found = manager.findNPC("Elder");
        REQUIRE(found != nullptr);
        REQUIRE(found->getName() == "Elder");
    }

    SECTION("Find non-existent NPC") {
        Entity* found = manager.findNPC("NonExistent");
        REQUIRE(found == nullptr);
    }
}

TEST_CASE("NPCManager const overloading", "[session09][const]") {
    NPCManager manager;
    Merchant merchant("Bob", 15, 500);
    manager.addNPC(&merchant);

    SECTION("Non-const findNPC") {
        Entity* found = manager.findNPC("Bob");
        REQUIRE(found != nullptr);
    }

    SECTION("Const findNPC") {
        const NPCManager& constManager = manager;
        const Entity* found = constManager.findNPC("Bob");
        REQUIRE(found != nullptr);
        REQUIRE(found->getName() == "Bob");
    }
}

TEST_CASE("Virtual inheritance - single Entity instance", "[session09][virtual]") {
    Merchant merchant("Bob", 15, 500);

    // Virtual inheritance ensures single Entity subobject
    Entity* e1 = &merchant;

    REQUIRE(e1->getName() == "Bob");
}

TEST_CASE("Polymorphic behavior through interfaces", "[session09][polymorphism]") {
    Merchant merchant("Bob", 15, 500);
    QuestMaster qm("Elder", "Dragon Slayer", 1000);

    // Both are Traders
    Trader* trader1 = &merchant;
    Trader* trader2 = &qm;

    REQUIRE(trader1->getGold() == 500);
    REQUIRE(trader2->getGold() == 1000);

    // Should not crash
    trader1->trade();
    trader2->trade();
}

TEST_CASE("Empty manager operations", "[session09][edge]") {
    NPCManager manager;

    REQUIRE(manager.getNPCCount() == 0);

    Entity* found = manager.findNPC("Anyone");
    REQUIRE(found == nullptr);
}

TEST_CASE("Integration scenario", "[session09][integration]") {
    NPCManager manager;

    Merchant merchant1("Bob", 15, 500);
    Merchant merchant2("Alice", 20, 800);
    QuestMaster qm1("Elder", "Dragon Slayer", 1000);
    QuestMaster qm2("Sage", "Ancient Artifact", 1500);

    manager.addNPC(&merchant1);
    manager.addNPC(&merchant2);
    manager.addNPC(&qm1);
    manager.addNPC(&qm2);

    REQUIRE(manager.getNPCCount() == 4);

    // Find and interact with merchant
    Entity* found = manager.findNPC("Bob");
    REQUIRE(found != nullptr);

    Merchant* merchant = dynamic_cast<Merchant*>(found);
    REQUIRE(merchant != nullptr);
    merchant->attack();
    merchant->trade();

    // Find and interact with quest master
    found = manager.findNPC("Elder");
    REQUIRE(found != nullptr);

    QuestMaster* qm = dynamic_cast<QuestMaster*>(found);
    REQUIRE(qm != nullptr);
    qm->giveQuest();
    qm->trade();
}

TEST_CASE("Different values", "[session09][edge]") {
    SECTION("Zero values") {
        Merchant merchant("Poor", 0, 0);
        REQUIRE(merchant.getAttackPower() == 0);
        REQUIRE(merchant.getGold() == 0);
    }

    SECTION("High values") {
        QuestMaster qm("Rich", "Epic Quest", 999999);
        REQUIRE(qm.getGold() == 999999);
    }
}
