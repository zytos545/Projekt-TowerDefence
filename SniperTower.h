#pragma once
#include "Tower.h"

class SniperTower : public Tower {
public:
    SniperTower(sf::Vector2f position);
    static const int PRICE = 220;
    
    
    void fire(const Enemy& target, std::vector<Projectile>& projectiles) override;
}; 
