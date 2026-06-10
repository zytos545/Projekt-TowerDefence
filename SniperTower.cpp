#include "SniperTower.h"
#include "Enemy.h"
#include "Projectile.h"

// Snajper: zasięg 400, strzał co 3.0s, obrażenia 50
SniperTower::SniperTower(sf::Vector2f position)
    : Tower("asets/textures/sniper2.png", position, 800.0f, 2.0f, 100,"Snajper",4000.f) {
}

void SniperTower::update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) {
    
    Tower::update(deltaTime, enemies, projectiles);
    
    
}s