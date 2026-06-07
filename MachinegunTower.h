#pragma once
#include "Tower.h"

class MachineGunTower : public Tower {
public:
    MachineGunTower(sf::Vector2f position);

    static const int PRICE = 30;
    void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) override;
}; 
