#include "enemy.h"
#include <cmath>

Enemy::Enemy(vector<sf::Vector2f> path, EnemyType type1)
{
    this->type = type1;
    waypoints = path;
    currentWaypoint = 0;

    shape.setRadius(20.f);
    shape.setOrigin(20.f, 20.f);

    if (type == Normal)
    {
        maxHp = 100;
        hp = maxHp;
        speed = 100.f;
        reward = 1;

        exp = 1;

    }
    else if (type == Fast)
    {
        maxHp = 200;
        hp = maxHp;
        speed = 160.f;
        reward = 2;
        exp = 5;
        shape.setFillColor(sf::Color::Yellow);
    }
    else if (type == Tank)
    {
        maxHp = 500;
        hp = maxHp;
        speed = 60.f;
        reward = 3;
        exp = 10;
        shape.setFillColor(sf::Color::Blue);
    }

    if (waypoints.size() > 0)
    {
        shape.setPosition(waypoints[0]);
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
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

    sf::Vector2f position = shape.getPosition();
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

    shape.move(direction * speed * deltaTime);
}

sf::Vector2f Enemy::getPosition() const
{
    return shape.getPosition();
}

sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
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