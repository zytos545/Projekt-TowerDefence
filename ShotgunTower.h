#pragma once
#include "Tower.h"

class ShotgunTower : public Tower {
public:
    ShotgunTower(sf::Vector2f position);

    // Nadpisujemy update - shotgun np. wystrzeliwuje kilka pocisków naraz pod różnymi kątami
    void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) override;
}; 
