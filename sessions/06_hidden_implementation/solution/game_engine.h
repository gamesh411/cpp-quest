#pragma once
#include <memory>
#include <string>

class GameEngine {
   private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

   public:
    GameEngine();
    ~GameEngine();

    GameEngine(GameEngine&&) noexcept;
    GameEngine& operator=(GameEngine&&) noexcept;

    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

    void addPlayer(const std::string& name, int health);
    void addEnemy(const std::string& name, int health);
    void update();
    void displayStatus() const;
    int getPlayerCount() const;
    int getEnemyCount() const;
};
