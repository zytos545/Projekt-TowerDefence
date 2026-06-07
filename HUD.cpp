#include "HUD.h"
#include "GameState.h"
#include <string>
#include <iostream>

HUD::HUD() {

    if (!font.loadFromFile("asets/fonts/Jersey_25/Jersey.ttf")) {
        std::cerr << "Blad: Nie mozna zaladowac pliku czcionki!" << std::endl;
    }

    moneyText.setFont(font);
    moneyText.setCharacterSize(36);
    moneyText.setFillColor(sf::Color::Yellow);
    moneyText.setPosition(20.f, 450.f);

    expText.setFont(font);
    expText.setCharacterSize(36);
    expText.setFillColor(sf::Color::Cyan);
    expText.setPosition(140.f, 450.f);

    hpText.setFont(font);
    hpText.setCharacterSize(36);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition(20.f, 500.f);

    waveText.setFont(font);
    waveText.setCharacterSize(36);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(140.f, 500.f);

    towerInfoText.setFont(font);
    towerInfoText.setCharacterSize(36);
    towerInfoText.setFillColor(sf::Color::Green);
    towerInfoText.setPosition(20.f, 550.f);
}

void HUD::update(const GameState& state) {
    moneyText.setString(std::to_string(state.money));
    expText.setString(std::to_string(state.expe));
    hpText.setString(std::to_string(state.playerHP));
    waveText.setString(std::to_string(state.currentWave));

    if (state.towerName != "Brak") {
        towerInfoText.setString(std::to_string(state.upgradeCost));
    }
    else {
        towerInfoText.setString("");
    }
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(moneyText);
    window.draw(expText);
    window.draw(hpText);
    window.draw(waveText);
    window.draw(towerInfoText);
}