#include "Game.h"
#include "SniperTower.h"
#include "ShotgunTower.h"
#include "MachinegunTower.h"
#include <algorithm>

// Konstruktor - łączymy mapę z Twoim oknem i wektorem wrogów
Game::Game() : window(sf::VideoMode(1280, 720), "Tower Defense"), currentSelection(SelectedTowerType::SNIPER), map() {
    window.setFramerateLimit(60);

    // Zamiast sztywnych kordynatów, dajemy pierwszemu wrogowi ścieżkę od kolegi!
    enemies.push_back(Enemy(map.getWaypoints()));
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }

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

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& p) { return !p.getIsActive(); }), projectiles.end());

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.isAlive(); }), enemies.end());
}

void Game::render() {
    window.clear(sf::Color::Black);

    // 1. Najpierw rysujemy mapę jako tło
    map.draw(window);

    // 2. Potem wrogów
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }

    // 3. Potem wieże (używamy -> zamiast . bo to inteligentne wskaźniki!)
    for (const auto& tower : towers) {
        tower->draw(window);
    }

    // 4. Na samym końcu pociski, żeby leciały "nad" wszystkim
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