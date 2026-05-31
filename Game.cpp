#include "Game.h"
#include "SniperTower.h"
#include "ShotgunTower.h"
#include "MachinegunTower.h"
#include <algorithm>

// Konstruktor - tutaj inicjalizujemy okno i stan początkowy
Game::Game() : window(sf::VideoMode(800, 600), "Tower Defense"), currentSelection(SelectedTowerType::SNIPER) {
    window.setFramerateLimit(60);

    // Dodajemy jednego testowego wroga na środku ekranu (pozycja 400x300, 100 HP)
    enemies.push_back(Enemy(sf::Vector2f(400.f, 300.f), 100));
}

// Główna pętla gry
void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}


// klawiatura, myszka
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Przechwytywanie wciśnięcia klawisza z klawiatury
        if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }

        // Przechwytywanie kliknięcia lewym przyciskiem myszy
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                const int TILE_SIZE = 64;

                int gridX = static_cast<int>(worldPos.x) / TILE_SIZE;
                int gridY = static_cast<int>(worldPos.y) / TILE_SIZE;

                sf::Vector2f centerPos(gridX * TILE_SIZE + TILE_SIZE / 2.0f,
                    gridY * TILE_SIZE + TILE_SIZE / 2.0f);

                bool isOccupied = false;
                for (const auto& tower : towers) {
                    if (tower->getPosition() == centerPos) { 
                        isOccupied = true;
                        break;
                    }
                }

                // Tworzenie odpowiedniego typu wieżyczki
                if (!isOccupied && currentSelection != SelectedTowerType::NONE) {
                    if (currentSelection == SelectedTowerType::SNIPER) {
                        towers.push_back(std::make_unique<SniperTower>(centerPos));
                    }
                    else if (currentSelection == SelectedTowerType::MACHINE_GUN) {
                        towers.push_back(std::make_unique<MachineGunTower>(centerPos));
                    }
                    else if (currentSelection == SelectedTowerType::SHOT_GUN) {
                        towers.push_back(std::make_unique<ShotgunTower>(centerPos));
                    }
                }
            }
        }
    }
}

void Game::update(float deltaTime) {
    
    for (auto& enemy : enemies) {
        enemy.update(deltaTime);
    }

    
    for (auto& tower : towers) {
        tower->update(deltaTime, enemies, projectiles);
    }

    
    for (auto& projectile : projectiles) {
        projectile.update(deltaTime);

        
        if (projectile.getIsActive()) {
            for (auto& enemy : enemies) {
                if (enemy.isAlive() && projectile.getBounds().intersects(enemy.getBounds())) {

                    enemy.takeDamage(projectile.getDamage()); 
                    projectile.deactivate();                  
                    break; 
                }
            }
        }
    }

    // 4. Czyszczenie pamięci (usuwanie martwych wrogów i zniszczonych pocisków)
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& p) { return !p.getIsActive(); }), projectiles.end());

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.isAlive(); }), enemies.end());
}
void Game::render() {
    window.clear(sf::Color::Black);
    for (const auto& tower : towers) {
        tower.draw(window);
    }
    
    for (const auto& projectile : projectiles) {
        projectile.draw(window);
    }
    window.display();
}
void Game::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Num1:
        currentSelection = SelectedTowerType::SNIPER;
        break;
    case sf::Keyboard::Num2:
        currentSelection = SelectedTowerType::MACHINE_GUN;
        break;
    case sf::Keyboard::Num3:
        currentSelection = SelectedTowerType::SHOT_GUN;
        break;
    case sf::Keyboard::Escape: 
        currentSelection = SelectedTowerType::NONE;
        break;
    default:
        break;
    }
}