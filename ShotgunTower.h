#pragma once
#include "Tower.h"

class ShotgunTower : public Tower {
public:
    ShotgunTower(sf::Vector2f position);
    static const int PRICE = 250;
    void fire(const Enemy& target, std::vector<Projectile>& projectiles) override;
}; 
