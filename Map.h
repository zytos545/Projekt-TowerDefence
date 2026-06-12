 #pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Map
{
public:
    Map();
    vector<sf::Vector2f> getWaypoints();
    void draw(sf::RenderWindow& window);

private:
    vector<sf::RectangleShape> pathTiles;
    vector<sf::Vector2f> waypoints;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};
