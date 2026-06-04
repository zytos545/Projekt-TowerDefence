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

    // metody dla wiezyczek i pociskow
    sf::Vector2f getPosition() const;
    float getDistanceTraveled() const;
    sf::FloatRect getBounds() const;
    void takeDamage(int damage);
    bool isAlive() const;
    int getReward() const;
private:
    sf::CircleShape shape;
    vector<sf::Vector2f> waypoints;
    int currentWaypoint;
    float speed;
    int reward; 
    
    int hp;
};