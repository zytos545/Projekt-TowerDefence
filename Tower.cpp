#include "Tower.h"
#include "Enemy.h"       
#include "Projectile.h"  
#include <cmath>         
#include <string>
Tower::Tower(const std::string& texturePath, sf::Vector2f position, float range, float cooldown, int damage, std::string n,float speed)
    : range(range), attackCooldown(cooldown), timeSinceLastAttack(0.0f), damage(damage),name(n),projectile_speed(speed) {

    if (texture.loadFromFile(texturePath)) {
        sprite.setTexture(texture);
    }

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    sprite.setPosition(position);
}

void Tower::update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles) {
    timeSinceLastAttack += deltaTime;

    const Enemy* target = nullptr;

    
    float maxProgress = -1.0f;

    sf::Vector2f towerPos = sprite.getPosition();


    for (const auto& enemy : enemies) {
        sf::Vector2f enemyPos = enemy.getPosition();

        float dx = enemyPos.x - towerPos.x;
        float dy = enemyPos.y - towerPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        
        if (distance <= range) {
            
            if (enemy.getDistanceTraveled() > maxProgress) {
                maxProgress = enemy.getDistanceTraveled();
                target = &enemy;
            }
        }
    }

   
    if (target != nullptr && timeSinceLastAttack >= attackCooldown) {
        timeSinceLastAttack = 0.0f;

        sf::Vector2f targetPos = target->getPosition();
        projectiles.push_back(Projectile(towerPos, targetPos, damage,projectile_speed));

      
        float angle = std::atan2(targetPos.y - towerPos.y, targetPos.x - towerPos.x) * 180.0f / 3.14159265f;
        sprite.setRotation(angle);
    }
}

void Tower::draw(sf::RenderTarget& target) const {
    target.draw(sprite);
}

sf::Vector2f Tower::getPosition() const {
    return sprite.getPosition();
}

float Tower::getRange() const {
    return range;
}
void Tower::upgrade() {
    if (level < maxLevel) {
        level++;
        damage += 10;        
        range += 20.0f;      
    }
}

int Tower::getLevel() const {
    return level;
}
sf::FloatRect Tower::getBounds() const {
    
    return sprite.getGlobalBounds();
}
string Tower::getName() const {
    return Tower::name;
}