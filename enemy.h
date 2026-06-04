#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Enemy
{
public:
    Enemy(vector<sf::Vector2f> path);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape shape;

    vector<sf::Vector2f> waypoints;

    int currentWaypoint;

    float speed;
};