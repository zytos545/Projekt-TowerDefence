
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Deklaracje zapowiadające
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

public:
    // Konstruktor
    Tower(const std::string& texturePath, sf::Vector2f position, float range, float cooldown, int damage);

    // Wirtualny destruktor 
    virtual ~Tower() = default;

    // Główna logika 
    virtual void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles);

    // Rysowanie wieży
    void draw(sf::RenderTarget& target) const;

    // Metody dostępowe (gettery)
    sf::Vector2f getPosition() const;
    float getRange() const;
};
