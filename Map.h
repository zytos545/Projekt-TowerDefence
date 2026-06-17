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
    bool isPositionOnPath(sf::FloatRect towerBounds) const; 
    sf::Vector2f snapToGrid(sf::Vector2f worldPos) const;
private:
    vector<sf::RectangleShape> pathTiles;
    vector<sf::Vector2f> waypoints;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture pathTexture;
};
