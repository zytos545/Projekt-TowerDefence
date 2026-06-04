#pragma once
#include "Tower.h"

class SniperTower : public Tower {
public:
    SniperTower(sf::Vector2f position);

    // Nadpisujemy update - snajper np. namierza wroga z największą ilością HP
    void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) override;
}; 
