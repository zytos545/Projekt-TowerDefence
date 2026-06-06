#include "ShotgunTower.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath>

// Shotgun: zasięg 100, strzał co 1.5s, obrażenia 20
ShotgunTower::ShotgunTower(sf::Vector2f position)
    : Tower("asets/textures/shot2.png", position, 100.0f, 1.5f, 20) {
}

void ShotgunTower::update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) {
    
    timeSinceLastAttack += deltaTime;

    
    const Enemy* target = nullptr;
    float minDistance = range;

    for (const auto& enemy : enemies) {
        
        float dx = enemy.getPosition().x - getPosition().x;
        float dy = enemy.getPosition().y - getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < minDistance) {
            minDistance = distance;
            target = &enemy;
        }
    }

    
    if (target != nullptr && timeSinceLastAttack >= attackCooldown) {

        
        float dx = target->getPosition().x - getPosition().x;
        float dy = target->getPosition().y - getPosition().y;
        float baseAngle = std::atan2(dy, dx);

        int numProjectiles = 4;
        float spreadAngle = 10.0f * (3.14159f / 180.0f); // 10 stopni rozrzutu
        float startOffset = -(numProjectiles - 1) / 2.0f * spreadAngle;

        for (int i = 0; i < numProjectiles; ++i) {
            float currentAngle = baseAngle + startOffset + (i * spreadAngle);
            float dirX = std::cos(currentAngle);
            float dirY = std::sin(currentAngle);

            
            sf::Vector2f fakeTarget(
                getPosition().x + dirX * range,
                getPosition().y + dirY * range
            );

            
            projectiles.push_back(Projectile(getPosition(), fakeTarget, damage));
        }

        
        timeSinceLastAttack = 0.0f;
    }
}