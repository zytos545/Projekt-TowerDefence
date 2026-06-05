#pragma once

#include <SFML/Graphics.hpp>

class HUD {
private:
    sf::Font font;
    sf::Text moneyText;
    sf::Text expText;
public:
    HUD();
    void update(int currentMoney, int currentExp); 
    void draw(sf::RenderWindow& window);
}; 
