#include "Game.h"
#include <vector>
#include <algorithm>
#include "SniperTower.h"
#include "ShotgunTower.h"
#include "MachinegunTower.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Tower Defence"),
    currentSelection(SelectedTowerType::SNIPER),
    map()
{
    window.setFramerateLimit(60);

    money = 150;

    spawnTimer = 0.f;
    spawnInterval = 2.f;
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            handleKeyPress(event.key.code);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                const int TILE_SIZE = 64;

                int gridX = static_cast<int>(worldPos.x) / TILE_SIZE;
                int gridY = static_cast<int>(worldPos.y) / TILE_SIZE;

                sf::Vector2f centerPos(
                    gridX * TILE_SIZE + TILE_SIZE / 2.0f,
                    gridY * TILE_SIZE + TILE_SIZE / 2.0f
                );

                bool isOccupied = false;

                for (const auto& tower : towers)
                {
                    if (tower->getPosition() == centerPos)
                    {
                        isOccupied = true;
                        break;
                    }
                }

                if (!isOccupied && currentSelection != SelectedTowerType::NONE)
                {
                    if (currentSelection == SelectedTowerType::SNIPER && money >= SniperTower::PRICE)
                    {
                        towers.push_back(std::make_unique<SniperTower>(centerPos));
                        money -= SniperTower::PRICE;
                    }
                    else if (currentSelection == SelectedTowerType::MACHINE_GUN && money >= MachineGunTower::PRICE)
                    {
                        towers.push_back(std::make_unique<MachineGunTower>(centerPos));
                        money -= MachineGunTower::PRICE;
                    }
                    else if (currentSelection == SelectedTowerType::SHOT_GUN && money >= ShotgunTower::PRICE)
                    {
                        towers.push_back(std::make_unique<ShotgunTower>(centerPos));
                        money -= ShotgunTower::PRICE;
                    }
                }
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                for (auto& tower : towers)
                {
                    if (tower->getBounds().contains(mousePos))
                    {
                        int upgradeCost = 100;

                        if (money >= upgradeCost && tower->getLevel() < 3)
                        {
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

void Game::update(float deltaTime)
{
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval)
    {
        enemies.push_back(Enemy(map.getWaypoints(), Normal));
        spawnTimer = 0.f;
    }

    if (currentSelection != SelectedTowerType::NONE)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        const int TILE_SIZE = 64;

        int gridX = static_cast<int>(mousePos.x) / TILE_SIZE;
        int gridY = static_cast<int>(mousePos.y) / TILE_SIZE;

        sf::Vector2f snappedPos(
            gridX * TILE_SIZE + TILE_SIZE / 2.0f,
            gridY * TILE_SIZE + TILE_SIZE / 2.0f
        );

        previewSprite.setPosition(snappedPos);
    }

    for (auto& enemy : enemies)
    {
        enemy.update(deltaTime);
    }

    for (auto& tower : towers)
    {
        tower->update(deltaTime, enemies, projectiles);
    }

    for (auto& projectile : projectiles)
    {
        projectile.update(deltaTime);

        if (projectile.getIsActive())
        {
            for (auto& enemy : enemies)
            {
                if (enemy.isAlive() && projectile.getBounds().intersects(enemy.getBounds()))
                {
                    enemy.takeDamage(projectile.getDamage());
                    if (!enemy.isAlive())
                    {
                        money += enemy.getReward();
                        experience += enemy.getExp();
                    }
                    projectile.deactivate();
                    break;
                }
            }
        }
    }

    projectiles.erase(
        std::remove_if(
            projectiles.begin(),
            projectiles.end(),
            [](const Projectile& projectile)
            {
                return !projectile.getIsActive();
            }
        ),
        projectiles.end()
    );

    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const Enemy& enemy)
            {
                return !enemy.isAlive();
            }
        ),
        enemies.end()
    );
    hud.update(money,experience);
}

void Game::render()
{
    window.clear(sf::Color::Black);

    map.draw(window);

    if (currentSelection != SelectedTowerType::NONE)
    {
        window.draw(previewSprite);
    }

    for (auto& enemy : enemies)
    {
        enemy.draw(window);
    }

    for (const auto& tower : towers)
    {
        tower->draw(window);
    }

    for (const auto& projectile : projectiles)
    {
        projectile.draw(window);
    }
    hud.draw(window);
    window.display();
}

void Game::handleKeyPress(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Num1)
    {
        currentSelection = SelectedTowerType::SNIPER;
        previewTexture.loadFromFile("asets/textures/sniper2.png");
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150));
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Num2)
    {
        currentSelection = SelectedTowerType::MACHINE_GUN;
        previewTexture.loadFromFile("asets/textures/machine2.png");
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150));
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Num3)
    {
        currentSelection = SelectedTowerType::SHOT_GUN;
        previewTexture.loadFromFile("asets/textures/shot2.png");
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150));
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Escape)
    {
        currentSelection = SelectedTowerType::NONE;
    }
}