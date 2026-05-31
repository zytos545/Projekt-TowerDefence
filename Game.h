#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>       
#include "Tower.h"
#include "Enemy.h"      
#include "Projectile.h" 

class Game {
private:
    sf::RenderWindow window;

    
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Tower>> towers; // Zmienione na wskaźniki dla polimorfizmu

    // System wyboru wieżyczek
    enum class SelectedTowerType { NONE, SNIPER, MACHINE_GUN, SHOT_GUN };
    SelectedTowerType currentSelection;

    // Prywatne metody pomocnicze
    void processEvents();
    void handleKeyPress(sf::Keyboard::Key key); // Zmiana typu stawiającej wieży
    void update(float deltaTime);
    void render();

public:
    Game();
    void run();
};
