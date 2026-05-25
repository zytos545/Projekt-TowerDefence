#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Map
{
public:
    Map();

    void draw(sf::RenderWindow& window);

private:
    vector<sf::RectangleShape> pathTiles;
};
