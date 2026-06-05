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
    int hp;
    int maxHp;
    int reward;
    EnemyType type;
};