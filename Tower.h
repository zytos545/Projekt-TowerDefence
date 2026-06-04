
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Enemy;
class Projectile;

class Tower {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    float range;
    float attackCooldown;
    float timeSinceLastAttack;
    int damage;
    int level;
    int maxLevel;
public:
    Tower(const std::string& texturePath, sf::Vector2f position, float range, float cooldown, int damage);
    virtual ~Tower() = default;
    virtual void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles);
    virtual void upgrade();
    int getLevel() const;
    void draw(sf::RenderTarget& target) const;
    sf::Vector2f getPosition() const;
    float getRange() const;
    sf::FloatRect getBounds() const;
};
