#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Enemy;
class Projectile;

class Tower {
protected:
    sf::SoundBuffer shotBuffer;
    sf::Sound shotSound;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f getShootPosition(sf::Vector2f targetPos) const;
    float range;
    float attackCooldown;
    float timeSinceLastAttack;
    bool isShootingAnimation;
    float shootingAnimationTimer;
    float shootingAnimationDuration;
    sf::Vector2f baseScale;
    int damage;
    int level;
    int maxLevel;
    float projectile_speed;
    std::string name;
public:
    Tower(const std::string& texturePath, sf::Vector2f position, float range, float cooldown, int damage,std::string n,float speed);
    virtual ~Tower() = default;
    virtual void update(float deltaTime, const std::vector<Enemy>& enemies, std::vector<Projectile>& projectiles);
    virtual void upgrade();
    int getLevel() const;
    void draw(sf::RenderTarget& target) const;
    sf::Vector2f getPosition() const;
    float getRange() const;
    std::string getName() const;
    sf::FloatRect getBounds() const;
    virtual void fire(const Enemy& target, std::vector<Projectile>& projectiles);
};
