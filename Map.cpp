#include "Map.h"
#include <cstdlib>
#include <ctime>


#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

// Zakładamy, że to jest wnętrze Twojego konstruktora Map::Map()
Map::Map()
{
    srand(static_cast<unsigned>(time(NULL)));

    sf::RectangleShape tile;
    tile.setFillColor(sf::Color(160, 82, 45));
    tile.setSize(sf::Vector2f(100.f, 100.f));

    // Wirtualna siatka (np. 20 kolumn na 10 wierszy), która pamięta, gdzie są kafelki
    std::vector<std::vector<bool>> grid(20, std::vector<bool>(10, false));

    // Pozycja startowa
    int currentX = 0;
    int currentY = 3;

    // Dodajemy pierwszy kafelek do siatki i na mapę
    grid[currentX][currentY] = true;
    tile.setPosition(currentX * 100.f, currentY * 100.f);
    pathTiles.push_back(tile);

    int lastDir = 0; 
    int maxGridX = 11; 

    while (currentX < maxGridX)
    {
        std::vector<int> possibleDirs;
        possibleDirs.push_back(0);

      
        if (currentY > 1 && lastDir != 2)
        {
          
            bool createsBlock = (currentX > 0 && grid[currentX - 1][currentY - 1]);
            if (!createsBlock)
            {
                possibleDirs.push_back(1);
            }
        }

  
        if (currentY < 5 && lastDir != 1)
        {
            
            bool createsBlock = (currentX > 0 && grid[currentX - 1][currentY + 1]);
            if (!createsBlock)
            {
                possibleDirs.push_back(2);
            }
        }

        
        int dir = possibleDirs[rand() % possibleDirs.size()];

        if (dir == 0) currentX++;
        else if (dir == 1) currentY--;
        else if (dir == 2) currentY++;

        // Zapisujemy ruch
        lastDir = dir;
        grid[currentX][currentY] = true;

        // Rysujemy kafelek
        tile.setPosition(currentX * 100.f, currentY * 100.f);
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