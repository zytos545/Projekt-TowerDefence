#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tower.h"
#include "enemy.h"
<<<<<<< HEAD
#include <vector>
class Game
{
public:
    Game();
    void run();
private:
    sf::RenderWindow window;
    Map map;
    vector<Enemy>enemies;
    float spawnTimer;
    float spawnInterval;
};
=======
#include "Projectile.h"
#include "Map.h"

class Game {
private:
    sf::RenderWindow window;

    Map map;
    int money; 

    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Tower>> towers;

    enum class SelectedTowerType { NONE, SNIPER, MACHINE_GUN, SHOT_GUN };
    SelectedTowerType currentSelection;

    
    sf::Texture previewTexture;
    sf::Sprite previewSprite;

   
    void processEvents();
    void handleKeyPress(sf::Keyboard::Key key);
    void update(float deltaTime);
    void render();

public:
    Game();
    void run();
};
>>>>>>> Towers_and_others
