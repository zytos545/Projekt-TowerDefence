#include "Map.h"
#include <cstdlib>
#include <ctime>

Map::Map()
{
    backgroundTexture.loadFromFile("asets/textures/oblock_background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        1920.f / backgroundTexture.getSize().x,
        1080.f / backgroundTexture.getSize().y
    );
    float nextx=0.f;
    float nexty = 400.f;
    const float tileSize = 70.f;
    sf::RectangleShape tile;
    for (int i = 0;i < 9;i++)
    {
        if(i%2==0)
        tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        if (i == 0)
            nextx = 0;
        else
            nextx += tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty -= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx -= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 7;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty += tileSize;
        tile.setPosition(nextx,nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx -= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty -= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 10;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx+= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 3;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty -= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx+= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 5;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty += tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 3;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx-= tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 4;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty += tileSize;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0; i < pathTiles.size(); i++)
    {
        sf::Vector2f position = pathTiles[i].getPosition();
        sf::Vector2f size = pathTiles[i].getSize();

        sf::Vector2f center(
            position.x + size.x / 2.f,
            position.y + size.y / 2.f
        );

        waypoints.push_back(center);
    }
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