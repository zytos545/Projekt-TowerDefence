#include "SniperTower.h"
#include "Enemy.h"
#include "Projectile.h"

// Snajper: duży zasięg (400), wolny strzał (co 3.0s), potężne obrażenia (50)
SniperTower::SniperTower(sf::Vector2f position)
    : Tower("assets/textures/sniper_tower.png", position, 400.0f, 3.0f, 50) {
}

void SniperTower::update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) {
    // Na tym etapie używamy domyślnego celowania z klasy bazowej
    Tower::update(deltaTime, enemies, projectiles);
}