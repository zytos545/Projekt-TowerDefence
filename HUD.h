#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"


class HUD {
private:
    sf::Font font;
    sf::Text moneyText;
    sf::Text expText;
    sf::Text hpText;
    sf::Text waveText;
    sf::Text towerInfoText;
    sf::Text selectedTowerText;
    sf::Text WaveDis;
   

public:
    HUD();
    
    void update(const GameState& state);
    void draw(sf::RenderWindow& window);
   
};