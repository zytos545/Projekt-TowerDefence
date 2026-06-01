#include "MachineGunTower.h"
#include "Enemy.h"
#include "Projectile.h"

// Karabin maszynowy: zasięg 150, strzał co 0.2s, obrażenia 5
MachineGunTower::MachineGunTower(sf::Vector2f position)
    : Tower("asets/textures/machine2.png", position, 150.0f, 0.2f, 5) {
}

void MachineGunTower::update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) {
    Tower::update(deltaTime, enemies, projectiles);
}