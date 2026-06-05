#include "HUD.h"
#include <string>
#include <iostream>

HUD::HUD() {
    
    if (!font.loadFromFile("asets/fonts/Jersey_25/Jersey.ttf")) {
        std::cerr << "Blad: Nie mozna zaladowac pliku czcionki!" << std::endl;
    }

   
    moneyText.setFont(font);
    moneyText.setCharacterSize(36);
    moneyText.setFillColor(sf::Color::Yellow);
    moneyText.setPosition(20.f, 20.f);

    
    expText.setFont(font);
    expText.setCharacterSize(36);
    expText.setFillColor(sf::Color::Cyan);
    expText.setPosition(20.f, 60.f); 
}

void HUD::update(int currentMoney, int currentExp) {
    
    moneyText.setString("Kasa: " + std::to_string(currentMoney));
    expText.setString("EXP: " + std::to_string(currentExp));
}

void HUD::draw(sf::RenderWindow& window) {
   
    window.draw(moneyText);
    window.draw(expText);
}