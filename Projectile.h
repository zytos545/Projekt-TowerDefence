#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f targetPos;
    float speed;
    int damage;
    bool isActive;

public:
    Projectile(sf::Vector2f startPos, sf::Vector2f targetPos, int damage);

    void update(float deltaTime);
    void draw(sf::RenderTarget& target) const;

    bool getIsActive() const;
    int getDamage() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void deactivate();
};
