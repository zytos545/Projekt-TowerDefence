#include "Game.h"
#include "SniperTower.h"
#include "ShotgunTower.h"
#include "MachinegunTower.h"
#include <algorithm>


Game::Game() : window(sf::VideoMode(1280, 720), "Tower Defense"), currentSelection(SelectedTowerType::SNIPER), map() {
    
    window.setFramerateLimit(60);
    money = 150;
    
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

                sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
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
        

        if (event.type == sf::Event::MouseButtonPressed) {
            //(PPM) - Ulepszanie
            if (event.mouseButton.button == sf::Mouse::Right) {

                
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                
                for (auto& tower : towers) {

                    
                    if (tower->getBounds().contains(mousePos)) {

                        
                        int upgradeCost = 100;

                        
                        if (money >= upgradeCost && tower->getLevel() < 3) {
                            money -= upgradeCost;    
                            tower->upgrade();        
                            break;                   
                        }
                    }
                }
            }

            
        }
    }
}

void Game::update(float deltaTime) {
    if (currentSelection != SelectedTowerType::NONE) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        const int TILE_SIZE = 64;

        
        int gridX = static_cast<int>(mousePos.x) / TILE_SIZE;
        int gridY = static_cast<int>(mousePos.y) / TILE_SIZE;

        
        sf::Vector2f snappedPos(gridX * TILE_SIZE + TILE_SIZE / 2.0f,
            gridY * TILE_SIZE + TILE_SIZE / 2.0f);

        previewSprite.setPosition(snappedPos);
    }
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

   
    map.draw(window);
    if (currentSelection != SelectedTowerType::NONE) {
        window.draw(previewSprite);
    }
   
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }

    
    for (const auto& tower : towers) {
        tower->draw(window);
    }

   
    for (const auto& projectile : projectiles) {
        projectile.draw(window);
    }

    window.display();
}

void Game::handleKeyPress(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Num1) {
        currentSelection = SelectedTowerType::SNIPER;
        previewTexture.loadFromFile("asets/textures/sniper2.png");
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150)); 
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Num2) {
        currentSelection = SelectedTowerType::MACHINE_GUN;
        previewTexture.loadFromFile("asets/textures/machine2.png"); 
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150));
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Num3) {
        currentSelection = SelectedTowerType::SHOT_GUN;
        previewTexture.loadFromFile("asets/textures/shot2.png");
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150));
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Escape) {
        currentSelection = SelectedTowerType::NONE;
    }
}