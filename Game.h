#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "enemy.h"
class Game
{
public:
    Game();
    void run();
private:
    sf::RenderWindow window;
    Map map;
    Enemy enemy;
};
