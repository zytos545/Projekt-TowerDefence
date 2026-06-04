#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "enemy.h"
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
