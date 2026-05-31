#include "ShotgunTower.h"
#include "Enemy.h"
#include "Projectile.h"

// Shotgun: zasięg (100), strzał (co 1.5s), obrażenia (20)
ShotgunTower::ShotgunTower(sf::Vector2f position)
    : Tower("assets/textures/shotgun_tower.png", position, 100.0f, 1.5f, 20) {
}

void ShotgunTower::update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) {
    Tower::update(deltaTime, enemies, projectiles);
}