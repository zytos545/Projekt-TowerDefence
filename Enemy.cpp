#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPos, int startHp)
    : position(startPos), distanceTraveled(0.0f), hp(startHp) {

    // Tymczasowy wygląd wroga 
    shape.setSize(sf::Vector2f(30.f, 30.f));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(15.f, 15.f);
    shape.setPosition(position);
}

void Enemy::update(float deltaTime) {
    // Miejsce na logikę poruszania 
}

void Enemy::draw(sf::RenderTarget& target) const {
    if (isAlive()) {
        target.draw(shape);
    }
}

void Enemy::takeDamage(int damage) {
    hp -= damage;
}

bool Enemy::isAlive() const {
    return hp > 0;
}

sf::Vector2f Enemy::getPosition() const {
    return position;
}

float Enemy::getDistanceTraveled() const {
    return distanceTraveled;
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}