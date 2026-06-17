#include "enemy.h"
#include <cmath>

Enemy::Enemy(vector<sf::Vector2f> path, EnemyType type1)
{
    static sf::Texture normalTexture;
    static sf::Texture fastTexture;
    static sf::Texture tankTexture;
    static bool texturesLoaded = false;

    if (!texturesLoaded)
    {
        normalTexture.loadFromFile("asets/textures/normal.png");
        fastTexture.loadFromFile("asets/textures/fast.png");
        tankTexture.loadFromFile("asets/textures/tank.png");

        normalTexture.setSmooth(true);
        fastTexture.setSmooth(true);
        tankTexture.setSmooth(true);

        texturesLoaded = true;
    }

    this->type = type1;
    waypoints = path;
    currentWaypoint = 0;
    velocity = sf::Vector2f(0.f, 0.f);

    if (type == EnemyType::Normal)
    {
        maxHp = 100;
        hp = maxHp;
        speed = 100.f;
        reward = 3;
        exp = 5;

        sprite.setTexture(normalTexture);
    }
    else if (type == EnemyType::Fast)
    {
        maxHp = 200;
        hp = maxHp;
        speed = 160.f;
        reward = 5;
        exp = 7;

        sprite.setTexture(fastTexture);
    }
    else if (type == EnemyType::Tank)
    {
        maxHp = 500;
        hp = maxHp;
        speed = 60.f;
        reward = 10;
        exp = 12;

        sprite.setTexture(tankTexture);
    }

    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.f,
        sprite.getLocalBounds().height / 2.f
    );

    float targetSize = 90.f;

    sprite.setScale(
        targetSize / sprite.getLocalBounds().width,
        targetSize / sprite.getLocalBounds().height
    );

    if (waypoints.size() > 0)
    {
        sprite.setPosition(waypoints[0]);
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Enemy::reachedEnd() const
{
    return currentWaypoint >= waypoints.size();
}

void Enemy::update(float deltaTime)
{
    if (currentWaypoint >= waypoints.size())
    {
        return;
    }

    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f target = waypoints[currentWaypoint];
    sf::Vector2f direction = target - position;

    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.f)
    {
        currentWaypoint++;
        return;
    }

    direction.x = direction.x / distance;
    direction.y = direction.y / distance;
    velocity = direction * speed;//velocity sluzy do obliczenia wyprzedzenia 
    sprite.move(direction * speed * deltaTime);
}

sf::Vector2f Enemy::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Enemy::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Enemy::takeDamage(int damage)
{
    hp -= damage;
}

bool Enemy::isAlive() const
{
    return hp > 0;
}

float Enemy::getDistanceTraveled() const
{
    return static_cast<float>(currentWaypoint);
}

int Enemy::getReward() const
{
    return reward;
}
int Enemy::getExp() const {
    return exp;
}
EnemyType Enemy::getType() const
{
    return type;
}
sf::Vector2f Enemy::getVelocity() const
{
    return velocity;
}