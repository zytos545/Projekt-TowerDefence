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
    isShootingAnimation = false;
    shootingAnimationTimer = 0.f;
    shootingAnimationDuration = 0.08f;
    baseScale = sprite.getScale();
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

        
        fire(*target, projectiles);
    }
    if (isShootingAnimation)
    {
        shootingAnimationTimer += deltaTime;

        float direction = 1.f;

        if (sprite.getScale().x < 0)
        {
            direction = -1.f;
        }

        if (shootingAnimationTimer < shootingAnimationDuration)
        {
            sprite.setScale(
                direction * std::abs(baseScale.x) * 1.18f,
                baseScale.y * 1.18f
            );
        }
        else
        {
            isShootingAnimation = false;

            sprite.setScale(
                direction * std::abs(baseScale.x),
                baseScale.y
            );
        }
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

sf::Vector2f Tower::getShootPosition(sf::Vector2f targetPos) const
{
    sf::Vector2f towerPos = sprite.getPosition();

    float directionX;

    if (targetPos.x < towerPos.x)
    {
        directionX = -1.f;
    }
    else
    {
        directionX = 1.f;
    }

    float offsetX = 35.f * directionX;
    float offsetY = 5.f;

    return sf::Vector2f(
        towerPos.x + offsetX,
        towerPos.y + offsetY
    );
}

void Tower::fire(const Enemy& target, std::vector<Projectile>& projectiles)
{
    sf::Vector2f towerPos = sprite.getPosition();
    sf::Vector2f targetPos = target.getPosition();

    sf::Vector2f shootPos = getShootPosition(targetPos);

    projectiles.push_back(Projectile(shootPos, targetPos, damage, projectile_speed));

    sf::Vector2f scale = sprite.getScale();

    if (targetPos.x < towerPos.x)
    {
        sprite.setScale(-std::abs(scale.x), scale.y);
    }
    else
    {
        sprite.setScale(std::abs(scale.x), scale.y);
    }
    isShootingAnimation = true;
    shootingAnimationTimer = 0.f;
    shotSound.play();
}