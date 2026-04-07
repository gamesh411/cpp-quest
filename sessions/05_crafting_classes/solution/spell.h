#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class SpellType { DAMAGE, HEALING, BUFF };

class Spell {
   private:
    std::string name_;
    int manaCost_;
    int power_;
    SpellType type_;

   public:
    Spell(const std::string& name, int cost, int power, SpellType type)
        : name_(name), manaCost_(cost), power_(power), type_(type) {}

    const std::string& getName() const { return name_; }
    int getManaCost() const { return manaCost_; }
    int getPower() const { return power_; }
    SpellType getType() const { return type_; }

    bool canCast(int availableMana) const { return availableMana >= manaCost_; }

    int cast() { return power_; }
};

class SpellBook {
   private:
    std::vector<Spell> spells_;
    int maxSpells_;

   public:
    SpellBook(int maxSpells) : maxSpells_(maxSpells) { spells_.reserve(maxSpells); }

    bool addSpell(const Spell& spell) {
        if (isFull()) {
            return false;
        }
        spells_.push_back(spell);
        return true;
    }

    const Spell* findSpell(const std::string& name) const {
        for (const auto& spell : spells_) {
            if (spell.getName() == name) {
                return &spell;
            }
        }
        return nullptr;
    }

    int getSpellCount() const { return spells_.size(); }

    bool isFull() const { return spells_.size() >= static_cast<size_t>(maxSpells_); }

    void listSpells() const {
        std::cout << "\nSpellbook contains " << spells_.size() << " spells:\n";
        for (const auto& spell : spells_) {
            std::cout << "  - " << spell.getName() << " (";
            switch (spell.getType()) {
                case SpellType::DAMAGE:
                    std::cout << "DAMAGE";
                    break;
                case SpellType::HEALING:
                    std::cout << "HEALING";
                    break;
                case SpellType::BUFF:
                    std::cout << "BUFF";
                    break;
            }
            std::cout << "): " << spell.getManaCost() << " mana, " << spell.getPower()
                      << " power\n";
        }
    }
};
