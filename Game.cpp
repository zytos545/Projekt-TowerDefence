#include "Game.h"
#include <vector>

Game::Game()
    : window(sf::VideoMode(1280, 720), "Tower Defence"),
    map()
{
    spawnTimer = 0.f;
    spawnInterval = 2.f;
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        spawnTimer += deltaTime;

        if (spawnTimer >= spawnInterval)
        {
            enemies.push_back(Enemy(map.getWaypoints(),Normal));

            spawnTimer = 0.f;
        }
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].update(deltaTime);
        }

        window.clear();

        map.draw(window);
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].draw(window);
        }

        window.display();
    }
}