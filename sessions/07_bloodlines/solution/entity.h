#pragma once
#include <algorithm>
#include <iostream>
#include <string>

class Entity {
   protected:
    std::string name_;
    int health_;
    int maxHealth_;

   public:
    Entity(const std::string& name, int maxHealth)
        : name_(name), health_(maxHealth), maxHealth_(maxHealth) {}

    virtual ~Entity() = default;

    const std::string& getName() const { return name_; }
    int getHealth() const { return health_; }
    int getMaxHealth() const { return maxHealth_; }

    void takeDamage(int amount) { health_ = std::max(0, health_ - amount); }

    void heal(int amount) { health_ = std::min(maxHealth_, health_ + amount); }

    bool isAlive() const { return health_ > 0; }

    virtual void display() const {
        std::cout << "Entity: " << name_ << "\n";
        std::cout << "  Health: " << health_ << "/" << maxHealth_ << "\n";
    }
};

class Character : public Entity {
   private:
    int mana_;
    int maxMana_;

   public:
    Character(const std::string& name, int maxHealth, int maxMana)
        : Entity(name, maxHealth), mana_(maxMana), maxMana_(maxMana) {}

    int getMana() const { return mana_; }
    int getMaxMana() const { return maxMana_; }

    void useMana(int amount) { mana_ = std::max(0, mana_ - amount); }

    void restoreMana(int amount) { mana_ = std::min(maxMana_, mana_ + amount); }

    void display() const override {
        std::cout << "Character: " << name_ << "\n";
        std::cout << "  Health: " << health_ << "/" << maxHealth_ << "\n";
        std::cout << "  Mana: " << mana_ << "/" << maxMana_ << "\n";
    }
};

class Enemy : public Entity {
   private:
    int experienceValue_;
    int goldDrop_;

   public:
    Enemy(const std::string& name, int maxHealth, int xp, int gold)
        : Entity(name, maxHealth), experienceValue_(xp), goldDrop_(gold) {}

    int getExperienceValue() const { return experienceValue_; }
    int getGoldDrop() const { return goldDrop_; }

    void display() const override {
        std::cout << "Enemy: " << name_ << "\n";
        std::cout << "  Health: " << health_ << "/" << maxHealth_ << "\n";
        std::cout << "  XP: " << experienceValue_ << ", Gold: " << goldDrop_ << "\n";
    }
};
