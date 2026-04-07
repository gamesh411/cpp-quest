#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Entity {
   protected:
    std::string name_;
    int health_;
    int maxHealth_;
    int attackPower_;

   public:
    Entity(const std::string& name, int maxHealth, int attackPower)
        : name_(name), health_(maxHealth), maxHealth_(maxHealth), attackPower_(attackPower) {}

    virtual ~Entity() = default;

    const std::string& getName() const { return name_; }
    int getHealth() const { return health_; }
    bool isAlive() const { return health_ > 0; }

    void takeDamage(int amount) { health_ = std::max(0, health_ - amount); }

    virtual void attack(Entity* target) = 0;
    virtual void defend() = 0;
    virtual std::string getType() const = 0;
};

class Warrior : public Entity {
   private:
    int armor_;

   public:
    Warrior(const std::string& name, int health, int attackPower, int armor)
        : Entity(name, health, attackPower), armor_(armor) {}

    void attack(Entity* target) override {
        std::cout << "⚔️ " << name_ << " slashes with sword for " << attackPower_ << " damage!\n";
        target->takeDamage(attackPower_);
    }

    void defend() override {
        std::cout << "🛡️ " << name_ << " raises shield (Armor: " << armor_ << ")\n";
    }

    std::string getType() const override { return "Warrior"; }

    int getArmor() const { return armor_; }
};

class Mage : public Entity {
   private:
    int mana_;

   public:
    Mage(const std::string& name, int health, int attackPower, int mana)
        : Entity(name, health, attackPower), mana_(mana) {}

    void attack(Entity* target) override {
        if (mana_ >= 10) {
            std::cout << "🔮 " << name_ << " casts fireball for " << attackPower_ << " damage!\n";
            target->takeDamage(attackPower_);
            mana_ -= 10;
        } else {
            std::cout << "💫 " << name_ << " has no mana!\n";
        }
    }

    void defend() override { std::cout << "✨ " << name_ << " casts shield spell\n"; }

    std::string getType() const override { return "Mage"; }

    int getMana() const { return mana_; }
};

class CombatSystem {
   private:
    std::vector<Entity*> combatants_;

   public:
    void addCombatant(Entity* entity) { combatants_.push_back(entity); }

    void executeTurn(int attackerIndex, int targetIndex) {
        if (attackerIndex >= 0 && attackerIndex < static_cast<int>(combatants_.size()) &&
            targetIndex >= 0 && targetIndex < static_cast<int>(combatants_.size())) {
            Entity* attacker = combatants_[attackerIndex];
            Entity* target = combatants_[targetIndex];

            std::cout << "\nTurn: " << attacker->getName() << " attacks " << target->getName()
                      << "\n";
            attacker->attack(target);
            std::cout << "✓ " << target->getName() << " took damage\n";
        }
    }

    void displayStatus() const {
        std::cout << "\nCombat Status:\n";
        for (const auto* entity : combatants_) {
            std::cout << "  " << entity->getType() << ": " << entity->getName()
                      << " (HP: " << entity->getHealth() << "/" << entity->getHealth() << ")";

            if (const Warrior* w = dynamic_cast<const Warrior*>(entity)) {
                std::cout << ", Armor: " << w->getArmor();
            } else if (const Mage* m = dynamic_cast<const Mage*>(entity)) {
                std::cout << ", Mana: " << m->getMana();
            }
            std::cout << "\n";
        }
    }

    int getCombatantCount() const { return combatants_.size(); }
};
