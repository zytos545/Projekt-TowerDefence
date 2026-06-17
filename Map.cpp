#include "Map.h"
#include <cstdlib>
#include <ctime>

Map::Map()
{
    pathTexture.loadFromFile("asets/textures/path_tile.png");

    backgroundTexture.loadFromFile("asets/textures/oblock_background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        1920.f / backgroundTexture.getSize().x,
        1080.f / backgroundTexture.getSize().y
    );

    const float tileSize = 72.f;

    float nextx = 0.f;
    float nexty = 432.f;

    auto addTile = [&](float x, float y)
        {
            sf::RectangleShape tile;
            tile.setSize(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(x, y);

            tile.setTexture(&pathTexture);

            pathTiles.push_back(tile);

            sf::Vector2f center(
                x + tileSize / 2.f,
                y + tileSize / 2.f
            );

            waypoints.push_back(center);
        };

    auto moveAndAdd = [&](int dx, int dy, int count)
        {
            for (int i = 0; i < count; i++)
            {
                nextx += dx * tileSize;
                nexty += dy * tileSize;

                addTile(nextx, nexty);
            }
        };

    addTile(nextx, nexty);

    moveAndAdd(1, 0, 8);   // w prawo
    moveAndAdd(0, -1, 2);  // w górę
    moveAndAdd(-1, 0, 2);  // w lewo
    moveAndAdd(0, 1, 7);   // w dół
    moveAndAdd(-1, 0, 2);  // w lewo
    moveAndAdd(0, -1, 2);  // w górę
    moveAndAdd(1, 0, 10);  // w prawo
    moveAndAdd(0, -1, 3);  // w górę
    moveAndAdd(1, 0, 2);   // w prawo
    moveAndAdd(0, 1, 5);   // w dół
    moveAndAdd(-1, 0, 3);  // w lewo
    moveAndAdd(0, 1, 4);   // w dół
}
vector<sf::Vector2f> Map::getWaypoints()
{
    return waypoints;
}

void Map::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    for (int i = 0; i < pathTiles.size(); i++)
    {
        window.draw(pathTiles[i]);
    }
}
bool Map::isPositionOnPath(sf::FloatRect towerBounds) const
{
    
    for (int i = 0; i < pathTiles.size(); i++)
    {
        
        sf::FloatRect tileBounds = pathTiles[i].getGlobalBounds();

   

        if (towerBounds.intersects(tileBounds)) {
            return true;
        }
        
    }


    return false;
}
sf::Vector2f Map::snapToGrid(sf::Vector2f worldPos) const
{
    const float tileSize = 72.f;

    int gridX = static_cast<int>(worldPos.x / tileSize);
    int gridY = static_cast<int>(worldPos.y / tileSize);

    return sf::Vector2f(
        gridX * tileSize + tileSize / 2.f,
        gridY * tileSize + tileSize / 2.f
    );
}