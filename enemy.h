#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
enum EnemyType
{
    Normal,
    Fast,
    Tank
};
class Enemy
{
public:
    Enemy(vector<sf::Vector2f> path,EnemyType type);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape shape;
    vector<sf::Vector2f> waypoints;
    int currentWaypoint;
    float speed;
    int health;
    int maxHealth;
    int reward;
    EnemyType type;
};