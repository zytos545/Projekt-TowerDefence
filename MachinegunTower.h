#pragma once
#include "Tower.h"

class MachineGunTower : public Tower {
public:
    MachineGunTower(sf::Vector2f position);

    // Nadpisujemy update - karabin maszynowy strzela bardzo szybko w najbliższego wroga
    void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) override;
}; 
