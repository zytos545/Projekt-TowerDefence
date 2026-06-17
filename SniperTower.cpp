#include "SniperTower.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath> 


SniperTower::SniperTower(sf::Vector2f position)
    : Tower("asets/textures/sniper2.png", position, 800.0f, 2.0f, 100, "Snajper", 1000.f)
{
    //grafika
    texture.loadFromFile("asets/textures/sniper2.png");
    texture.setSmooth(true);

    sprite.setTexture(texture);

    sprite.setOrigin(
        texture.getSize().x / 2.f,
        texture.getSize().y / 2.f
    );

    sprite.setPosition(position);

    float targetSize = 90.f;

    sprite.setScale(
        targetSize / texture.getSize().x,
        targetSize / texture.getSize().y
    );
    baseScale = sprite.getScale();

    //dzwiek
    if (shotBuffer.loadFromFile("asets/sounds/sniper.wav"))
    {
        shotSound.setBuffer(shotBuffer);
        shotSound.setVolume(10.f);
    }
}
void SniperTower::fire(const Enemy& target, std::vector<Projectile>& projectiles)
{
    sf::Vector2f towerPos = sprite.getPosition();
    sf::Vector2f enemyPos = target.getPosition();
    sf::Vector2f enemyVel = target.getVelocity();

    sf::Vector2f D = enemyPos - towerPos;

    float vE_squared = std::pow(enemyVel.x, 2.f) + std::pow(enemyVel.y, 2.f);
    float vP_squared = std::pow(projectile_speed, 2.f);

    float A = vE_squared - vP_squared;
    float B = 2.0f * ((D.x * enemyVel.x) + (D.y * enemyVel.y));
    float C = std::pow(D.x, 2.f) + std::pow(D.y, 2.f);

    float delta = (B * B) - (4.0f * A * C);

    sf::Vector2f aimPoint = enemyPos;

    if (delta >= 0.0f && A != 0.0f)
    {
        float t1 = (-B - std::sqrt(delta)) / (2.0f * A);
        float t2 = (-B + std::sqrt(delta)) / (2.0f * A);

        float t = 0.0f;

        if (t1 > 0.0f && t2 > 0.0f)
        {
            if (t1 < t2)
            {
                t = t1;
            }
            else
            {
                t = t2;
            }
        }
        else if (t1 > 0.0f)
        {
            t = t1;
        }
        else if (t2 > 0.0f)
        {
            t = t2;
        }

        if (t > 0.0f)
        {
            aimPoint.x = enemyPos.x + enemyVel.x * t;
            aimPoint.y = enemyPos.y + enemyVel.y * t;
        }
    }

    sf::Vector2f shootPos = getShootPosition(aimPoint);

    projectiles.push_back(Projectile(shootPos, aimPoint, damage, projectile_speed));

    sprite.setRotation(0.f);

    sf::Vector2f scale = sprite.getScale();

    if (aimPoint.x < towerPos.x)
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