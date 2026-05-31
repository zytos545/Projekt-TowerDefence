#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float distanceTraveled;
    int hp;

public:
    Enemy(sf::Vector2f startPos, int startHp);

    void update(float deltaTime);
    void draw(sf::RenderTarget& target) const;

    void takeDamage(int damage);
    bool isAlive() const;

    sf::Vector2f getPosition() const;
    float getDistanceTraveled() const;
    sf::FloatRect getBounds() const; 
};