	#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Tower Defence"),
    map(),
    enemy(map.getWaypoints())
{
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

        enemy.update(deltaTime);

        window.clear();

        map.draw(window);
        enemy.draw(window);

        window.display();
    }
}