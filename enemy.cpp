#include "enemy.h"
#include <cmath> 


Enemy::Enemy(vector<sf::Vector2f> path)
{
    waypoints = path;
    currentWaypoint = 0;
    speed = 100.f;

 
    hp = 100;
    reward = 15;
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(20.f, 20.f);

    if (waypoints.size() > 0)
    {
        shape.setPosition(waypoints[0]);
    }
}


void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
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



sf::Vector2f Enemy::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds(); 
}

void Enemy::takeDamage(int damage) {
    hp -= damage; 
}

bool Enemy::isAlive() const {
    return hp > 0; 
}

float Enemy::getDistanceTraveled() const {
    
    return static_cast<float>(currentWaypoint);
}
int Enemy::getReward() const {
    return reward;
}