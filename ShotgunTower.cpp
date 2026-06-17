#include "ShotgunTower.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath> 


ShotgunTower::ShotgunTower(sf::Vector2f position)
    : Tower("asets/textures/shot2.png", position, 250.0f, 1.5f, 40, "Strzelba", 500.f)
{
    //grafika
    texture.loadFromFile("asets/textures/shot2.png");
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
    if (shotBuffer.loadFromFile("asets/sounds/shotgun.wav"))
    {
        shotSound.setBuffer(shotBuffer);
        shotSound.setVolume(10.f);
    }
}

void ShotgunTower::fire(const Enemy& target, std::vector<Projectile>& projectiles)
{
    sf::Vector2f towerPos = sprite.getPosition();
    sf::Vector2f targetPos = target.getPosition();

    sf::Vector2f shootPos = getShootPosition(targetPos);

    float dx = targetPos.x - towerPos.x;
    float dy = targetPos.y - towerPos.y;
    float baseAngle = std::atan2(dy, dx);

    float spreadAngles[3] = { -0.26f, 0.0f, 0.26f };

    for (int i = 0; i < 3; i++)
    {
        float currentAngle = baseAngle + spreadAngles[i];

        sf::Vector2f spreadDir;
        spreadDir.x = std::cos(currentAngle);
        spreadDir.y = std::sin(currentAngle);

        sf::Vector2f fakeTargetPos;
        fakeTargetPos.x = shootPos.x + spreadDir.x * 1000.0f;
        fakeTargetPos.y = shootPos.y + spreadDir.y * 1000.0f;

        projectiles.push_back(Projectile(shootPos, fakeTargetPos, damage, projectile_speed));
    }

    sprite.setRotation(0.f);

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