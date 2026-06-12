#include "ShotgunTower.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath> 


ShotgunTower::ShotgunTower(sf::Vector2f position)
    : Tower("asets/textures/shotgun2.png", position, 250.0f, 1.5f, 40, "Strzelba", 500.f) {
}

void ShotgunTower::fire(const Enemy& target, std::vector<Projectile>& projectiles) {
    sf::Vector2f towerPos = sprite.getPosition();
    sf::Vector2f targetPos = target.getPosition();


    float dx = targetPos.x - towerPos.x;
    float dy = targetPos.y - towerPos.y;
    float baseAngle = std::atan2(dy, dx);

   
    float spreadAngles[3] = { -0.26f, 0.0f, 0.26f };

 
    for (int i = 0; i < 3; i++) {
        
        float currentAngle = baseAngle + spreadAngles[i];

        
        sf::Vector2f spreadDir;
           spreadDir.x = std::cos(currentAngle);
           spreadDir.y = std::sin(currentAngle);

        sf::Vector2f fakeTargetPos;
        fakeTargetPos.x = towerPos.x + (spreadDir.x * 1000.0f);
        fakeTargetPos.y = towerPos.y + (spreadDir.y * 1000.0f);

        
        projectiles.push_back(Projectile(towerPos, fakeTargetPos, damage, projectile_speed));
    }

    float spriteAngle = baseAngle * 180.0f / 3.14159265f;
    sprite.setRotation(spriteAngle);
}