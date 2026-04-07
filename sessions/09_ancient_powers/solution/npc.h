#pragma once
#include <iostream>
#include <string>
#include <vector>

class Combatant {
   public:
    virtual ~Combatant() = default;
    virtual void attack() = 0;
    virtual int getAttackPower() const = 0;
};

class Trader {
   public:
    virtual ~Trader() = default;
    virtual void trade() = 0;
    virtual int getGold() const = 0;
};

class QuestGiver {
   public:
    virtual ~QuestGiver() = default;
    virtual void giveQuest() = 0;
    virtual std::string getQuestName() const = 0;
};

class Entity {
   protected:
    std::string name_;

   public:
    Entity(const std::string& name) : name_(name) {}
    virtual ~Entity() = default;

    const std::string& getName() const { return name_; }
};

class Merchant : public virtual Entity, public Combatant, public Trader {
   private:
    int attackPower_;
    int gold_;

   public:
    Merchant(const std::string& name, int attackPower, int gold)
        : Entity(name), attackPower_(attackPower), gold_(gold) {}

    void attack() override { std::cout << "⚔️ " << name_ << " defends the shop!\n"; }

    int getAttackPower() const override { return attackPower_; }

    void trade() override { std::cout << "💰 " << name_ << " sells goods\n"; }

    int getGold() const override { return gold_; }
};

class QuestMaster : public virtual Entity, public QuestGiver, public Trader {
   private:
    std::string questName_;
    int gold_;

   public:
    QuestMaster(const std::string& name, const std::string& quest, int gold)
        : Entity(name), questName_(quest), gold_(gold) {}

    void giveQuest() override {
        std::cout << "📜 " << name_ << " offers quest: " << questName_ << "\n";
    }

    std::string getQuestName() const override { return questName_; }

    void trade() override { std::cout << "💰 " << name_ << " trades rare items\n"; }

    int getGold() const override { return gold_; }
};

class NPCManager {
   private:
    std::vector<Entity*> npcs_;

   public:
    void addNPC(Entity* npc) { npcs_.push_back(npc); }

    Entity* findNPC(const std::string& name) {
        for (auto* npc : npcs_) {
            if (npc->getName() == name) {
                return npc;
            }
        }
        return nullptr;
    }

    const Entity* findNPC(const std::string& name) const {
        for (auto* npc : npcs_) {
            if (npc->getName() == name) {
                return npc;
            }
        }
        return nullptr;
    }

    int getNPCCount() const { return npcs_.size(); }
};
