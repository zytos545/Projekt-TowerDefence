#pragma once
#include "Tower.h"

class SniperTower : public Tower {
public:
    SniperTower(sf::Vector2f position);
    static const int PRICE = 70;
    
    void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) override;
}; 
