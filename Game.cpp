	#include "Game.h"

Game::Game(): window(sf::VideoMode(1280, 720), "Tower Defence")
{

}

void Game::run()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		map.draw(window);
		window.display();
	}
}