#include "Game.h"
#include <vector>
#include <algorithm>
#include "SniperTower.h"
#include "ShotgunTower.h"
#include "MachinegunTower.h"

#include "GameState.h"


Game::Game()
    : window(sf::VideoMode(1920, 1080), "Tower Defence"),
    currentSelection(SelectedTowerType::SNIPER),
    map()
{
    window.setFramerateLimit(60);
    gameover = false;
    gameState.playerHP = 100;
    gameState.money = 150;

    gamewon = false;



    spawnTimer = 0.f;
    spawnInterval = 2.f;
    waves = createWaves();

    gameState.currentWave = 0;
    currentEnemyInWave = 0;

    waveActive = true;

    spawnTimer = 0.f;
    spawnInterval = 1.5f;

    timeBetweenWaves = 5.f;
    waveBreakTimer = 0.f;
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

                    if (currentSelection == SelectedTowerType::SNIPER && gameState.money >= SniperTower::PRICE)

                    {
                        towers.push_back(std::make_unique<SniperTower>(centerPos));
                        gameState.money -= SniperTower::PRICE;
                    }

                    else if (currentSelection == SelectedTowerType::MACHINE_GUN && gameState.money >= MachineGunTower::PRICE)
                    {
                        towers.push_back(std::make_unique<MachineGunTower>(centerPos));
                        gameState.money -= MachineGunTower::PRICE;
                    }

                    else if (currentSelection == SelectedTowerType::SHOT_GUN && gameState.money >= ShotgunTower::PRICE)
                    {
                        towers.push_back(std::make_unique<ShotgunTower>(centerPos));
                        gameState.money -= ShotgunTower::PRICE;
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

                        if (gameState.money >= upgradeCost && tower->getLevel() < 3)
                        {
                            gameState.money -= upgradeCost;
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
    if (gameover)
    {
        return;
    }

    if (gameState.currentWave < waves.size())
    {
        if (waveActive)
        {
            spawnTimer += deltaTime;

            if (spawnTimer >= spawnInterval)
            {
                if (currentEnemyInWave < waves[gameState.currentWave].size())
                {
                    EnemyType enemyType = waves[gameState.currentWave][currentEnemyInWave];

                    enemies.push_back(Enemy(map.getWaypoints(), enemyType));

                    currentEnemyInWave++;

                    spawnTimer = 0.f;
                }
                else
                {
                    waveActive = false;
                    waveBreakTimer = 0.f;
                }
            }
        }
        else
        {
            if (enemies.empty())
            {
                waveBreakTimer += deltaTime;

                if (waveBreakTimer >= timeBetweenWaves)
                {
                    gameState.currentWave++;
                    currentEnemyInWave = 0;
                    waveActive = true;
                    spawnTimer = 0.f;
                }
            }
        }
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
//tracenie HP gracza
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].reachedEnd())
        {
            gameState.playerHP--;

            enemies.erase(enemies.begin() + i);

            i--;

            if (gameState.playerHP <= 0)
            {
                gameover = true;
            }
        }
    }


    
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool isHovering = false;
    std::string hoveredName = "Brak";
    int hoveredUpgradeCost = 0;


    for (auto& tower : towers)
    {
        tower->update(deltaTime, enemies, projectiles);

        if (!isHovering && tower->getBounds().contains(mousePos))
        {
            isHovering = true;
            hoveredName = tower->getName();
            hoveredUpgradeCost = 100;       
        }
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
                        gameState.money += enemy.getReward();
                        gameState.expe += enemy.getExp();
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
//kasowanie przeciwnikow
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
    if (gameState.currentWave >= waves.size() && enemies.empty())
    {
        gamewon = true;
        gameover = true;
    }


    GameState currentState;
    currentState.money = gameState.money;
    currentState.playerHP = gameState.playerHP;
    currentState.currentWave = gameState.currentWave;
    currentState.expe = gameState.expe;

    if (isHovering)
    {
        currentState.towerName = hoveredName;
        currentState.upgradeCost = hoveredUpgradeCost;
        currentState.isUpgrade = true; 
    }
    else if (currentSelection != SelectedTowerType::NONE)
    {
        currentState.isUpgrade = false; 
        if (currentSelection == SelectedTowerType::SNIPER)
        {
            currentState.towerName = "Snajper";
            currentState.upgradeCost = SniperTower::PRICE;
        }
        else if (currentSelection == SelectedTowerType::MACHINE_GUN)
        {
            currentState.towerName = "Karabin";
            currentState.upgradeCost = MachineGunTower::PRICE;
        }
        else if (currentSelection == SelectedTowerType::SHOT_GUN)
        {
            currentState.towerName = "Strzelba";
            currentState.upgradeCost = ShotgunTower::PRICE;
        }
    }
    else
    {
        currentState.towerName = "Brak";
        currentState.upgradeCost = 0;
        currentState.isUpgrade = false;
    }

    hud.update(currentState);

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
        previewTexture.loadFromFile("assets/textures/shot2.png");
        previewSprite.setTexture(previewTexture, true);
        previewSprite.setColor(sf::Color(255, 255, 255, 150));
        previewSprite.setOrigin(previewTexture.getSize().x / 2.f, previewTexture.getSize().y / 2.f);
    }
    else if (key == sf::Keyboard::Escape)
    {
        currentSelection = SelectedTowerType::NONE;
    }
}
void addEnemiesToWave(vector<EnemyType>& wave, EnemyType type, int count)
{
    for (int i = 0; i < count; i++)
    {
        wave.push_back(type);
    }
}
vector<vector<EnemyType>> Game::createWaves()
{
    vector<vector<EnemyType>> newWaves;

    vector<EnemyType> wave1;
    addEnemiesToWave(wave1, Normal, 10);
    newWaves.push_back(wave1);

    vector<EnemyType> wave2;
    addEnemiesToWave(wave2, Normal, 10);
    addEnemiesToWave(wave2, Fast, 5);
    newWaves.push_back(wave2);

    vector<EnemyType> wave3;
    addEnemiesToWave(wave3, Normal, 15);
    addEnemiesToWave(wave3, Fast, 8);
    addEnemiesToWave(wave3, Tank, 3);
    newWaves.push_back(wave3);

    return newWaves;
}
