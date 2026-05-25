#include "Map.h"
#include <cstdlib>
#include <ctime>

Map::Map()
{
    const float tileSize = 50.f;
    sf::RectangleShape tile;
    for (int i = 0;i < 10;i++)
    {
        if(i%2==0)
        tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        tile.setPosition(40.f+i*50.f, 250.f);
        pathTiles.push_back(tile);
    }
    float nexty,nextx;
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty = 200 - i * 50.f;
        tile.setPosition(490.f, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx = 440.f - 50 * i;
        tile.setPosition(440.f-50*i, nexty);
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 7;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nexty += 50;
        tile.setPosition(nextx,nexty );
        pathTiles.push_back(tile);
    }
    for (int i = 0;i < 2;i++)
    {
        if (i % 2 == 0)
            tile.setFillColor(sf::Color(150, 150, 150));
        else
            tile.setFillColor(sf::Color(150, 150, 200));
        tile.setSize(sf::Vector2f(tileSize, tileSize));
        nextx -= 50;
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
        nexty -= 50;
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
        nextx+=50;
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
        nexty -= 50;
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
        nextx+= 50;
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
        nexty += 50;
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
        nextx-= 50;
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
        nexty += 50;
        tile.setPosition(nextx, nexty);
        pathTiles.push_back(tile);
    }
}


void Map::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < pathTiles.size(); i++)
    {
        window.draw(pathTiles[i]);
    }
}