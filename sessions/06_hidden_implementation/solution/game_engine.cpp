#include "game_engine.h"

#include <iostream>
#include <vector>

struct GameEngine::Impl {
    struct Entity {
        std::string name;
        int health;
    };

    std::vector<Entity> players;
    std::vector<Entity> enemies;
    int turnCount;

    Impl() : turnCount(0) {}
};

GameEngine::GameEngine() : pimpl_(std::make_unique<Impl>()) {}

GameEngine::~GameEngine() = default;

GameEngine::GameEngine(GameEngine&&) noexcept = default;
GameEngine& GameEngine::operator=(GameEngine&&) noexcept = default;

void GameEngine::addPlayer(const std::string& name, int health) {
    pimpl_->players.push_back({name, health});
}

void GameEngine::addEnemy(const std::string& name, int health) {
    pimpl_->enemies.push_back({name, health});
}

void GameEngine::update() {
    pimpl_->turnCount++;
}

void GameEngine::displayStatus() const {
    std::cout << "\nGame Status:\n";
    std::cout << "Players: " << pimpl_->players.size() << "\n";
    for (const auto& p : pimpl_->players) {
        std::cout << "  - " << p.name << " (HP: " << p.health << ")\n";
    }
    std::cout << "Enemies: " << pimpl_->enemies.size() << "\n";
    for (const auto& e : pimpl_->enemies) {
        std::cout << "  - " << e.name << " (HP: " << e.health << ")\n";
    }
    std::cout << "Turn: " << pimpl_->turnCount << "\n";
}

int GameEngine::getPlayerCount() const {
    return pimpl_->players.size();
}

int GameEngine::getEnemyCount() const {
    return pimpl_->enemies.size();
}
