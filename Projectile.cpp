#include "Projectile.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f targetPos, int damage, float speed)
    : position(startPos), targetPos(targetPos), damage(damage), speed(speed), isActive(true) {
    
    shape.setRadius(4.0f);
    shape.setFillColor(sf::Color::Black);

    
    shape.setOrigin(4.0f, 4.0f);
    shape.setPosition(position);

    
    float dx = targetPos.x - startPos.x;
    float dy = targetPos.y - startPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    
    if (distance > 0) {
        velocity.x = (dx / distance) * speed;
        velocity.y = (dy / distance) * speed;
    }
    else {
        velocity = sf::Vector2f(0.f, 0.f);
    }
}

void Projectile::update(float deltaTime) {
    if (!isActive) return;

    
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    shape.setPosition(position);

    
    float dx = targetPos.x - position.x;
    float dy = targetPos.y - position.y;
    float distanceToTarget = std::sqrt(dx * dx + dy * dy);

    
    if (distanceToTarget < 15.0f) {
        isActive = false;
    }
}

void Projectile::draw(sf::RenderTarget& target) const {
    if (isActive) {
        target.draw(shape);
    }
}

bool Projectile::getIsActive() const {
    return isActive;
}

int Projectile::getDamage() const {
    return damage;
}

sf::Vector2f Projectile::getPosition() const {
    return position;
}
sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}

void Projectile::deactivate() {
    isActive = false;
}