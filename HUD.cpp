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
    moneyText.setPosition(1600.f, 450.f);

    expText.setFont(font);
    expText.setCharacterSize(36);
    expText.setFillColor(sf::Color::Cyan);
    expText.setPosition(1400.f, 450.f);

    hpText.setFont(font);
    hpText.setCharacterSize(36);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition(1600.f, 550.f);

    waveText.setFont(font);
    waveText.setCharacterSize(36);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(1400.f, 550.f);

    towerInfoText.setFont(font);
    towerInfoText.setCharacterSize(36);
    towerInfoText.setFillColor(sf::Color::Green);
    towerInfoText.setPosition(1600.f, 650.f);

    selectedTowerText.setFont(font);
    selectedTowerText.setCharacterSize(32);
    selectedTowerText.setFillColor(sf::Color::Magenta);
    selectedTowerText.setPosition(1400.f,650.f);

    WaveDis.setFont(font);
    WaveDis.setCharacterSize(28);
    WaveDis.setFillColor(sf::Color::Yellow);
    WaveDis.setPosition(1400.f, 10.f);
    
}

void HUD::update(const GameState& state) {
    moneyText.setString("Kasa: " + std::to_string(state.money));
    expText.setString("EXP: " + std::to_string(state.expe));
    hpText.setString("HP: " + std::to_string(state.playerHP));
    waveText.setString("Fala: " + std::to_string(state.currentWave));
    WaveDis.setString(L"Sterowanie:\nEnter aby rozpocząć falę.\nPod 1, 2,  3 znajduje się:\nsnajper, karabin i strzelba.\nNaciśnij esc aby anulować wybór.\nNaciśnij PPM na wieżę aby ją ulepszyć.");
    if (state.towerName != "Brak" ) {
        towerInfoText.setString("Koszt: " + std::to_string(state.upgradeCost));
        selectedTowerText.setString("Typ: " + state.towerName);
    }
    else {
        towerInfoText.setString("");
        selectedTowerText.setString("");
    }
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(moneyText);
    window.draw(expText);
    window.draw(hpText);
    window.draw(waveText);
    window.draw(towerInfoText);
    window.draw(selectedTowerText);
    window.draw(WaveDis);
}