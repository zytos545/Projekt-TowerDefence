#include "Game.h"
#include <vector>
#include <algorithm>
#include "SniperTower.h"
#include "ShotgunTower.h"
#include "MachinegunTower.h"
#include <iostream>
#include "HUD.h"

Game::Game()
    : window(sf::VideoMode(1920, 1080), "Tower Defence"),
    currentSelection(SelectedTowerType::MACHINE_GUN),
    map()
{
    waitingForNextWave = true;
    window.setFramerateLimit(60);
    gameover = false;
    gameState.playerHP = 100;
    gameState.money = 650;
    gameStarted = false;
    gamewon = false;
    winScreen.setSize(sf::Vector2f(1920.f, 1080.f));
    winScreen.setFillColor(sf::Color::Black);
    winScreen.setPosition(0.f, 0.f);

    if (!winFont.loadFromFile("asets/fonts/Jersey_25/Jersey.ttf"))
    {
        std::cerr << "Blad: Nie mozna zaladowac czcionki konca gry!" << std::endl;
    }

    winText.setFont(winFont);
    winText.setString("WYGRANA!");
    winText.setCharacterSize(140);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(690.f, 420.f);

    loseText.setFont(winFont);
    loseText.setString("PRZEGRANA!");
    loseText.setCharacterSize(140);
    loseText.setFillColor(sf::Color::Red);
    loseText.setPosition(610.f, 420.f);

    waves = createWaves();

    gameState.currentWave = 0;
    currentEnemyInWave = 0;

    waveActive = false;

    spawnTimer = 0.f;
    spawnInterval = 0.5f;

    timeBetweenWaves = 5.f;
    waveBreakTimer = 0.f;

    State = MenuState::MENU;

    // Wczytaj czcionkę (użyj ścieżki do czcionki, którą już masz np. w HUD)
    if (!menuFont.loadFromFile("asets/fonts/Jersey_25/Jersey.ttf")) {
      
    }

  
    playButtonText.setFont(menuFont);
    playButtonText.setString("GRAJ");
    playButtonText.setCharacterSize(70);
    playButtonText.setFillColor(sf::Color::Green);

    exitButtonText.setFont(menuFont); 
    exitButtonText.setString("X");    
    exitButtonText.setCharacterSize(100);
    exitButtonText.setFillColor(sf::Color::Red);
    exitButtonText.setPosition(55.f, 7.f);
    if (menuBgTexture.loadFromFile("asets/textures/menu_bg_.png"))
    {
        menuBgSprite.setTexture(menuBgTexture);

        
        float scaleX = static_cast<float>(window.getSize().x) / menuBgTexture.getSize().x;
        float scaleY = static_cast<float>(window.getSize().y) / menuBgTexture.getSize().y;

        
        menuBgSprite.setScale(scaleX, scaleY);
    }
    sf::FloatRect textRect = playButtonText.getLocalBounds();
    playButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    playButtonText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
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
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        // ---------------- OBSŁUGA MENU ----------------
        if (State == MenuState::MENU)
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                

               
                if (playButtonText.getGlobalBounds().contains(mousePos))
                {
                    State = MenuState::PLAYING;
                }
                if (exitButtonText.getGlobalBounds().contains(mousePos))
                {
                    window.close(); 
                }

            }
        }
        // ---------------- OBSŁUGA GRY ----------------
        else if (State == MenuState::PLAYING)
        {
         

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
                    if (hud.getMenuButtonBounds().contains(mousePos))
                    {
                        State = MenuState::MENU;
                        continue; 
                    }
                    sf::Vector2f centerPos = map.snapToGrid(worldPos);

                    bool isOccupied = false;

                    for (const auto& tower : towers)
                    {   
                        if (tower->getPosition() == centerPos)
                        {
                            isOccupied = true;
                            break;
                        }
                    }

                    const float TILE_SIZE = 70.f;

                    sf::FloatRect proposedBounds(
                        centerPos.x - TILE_SIZE / 2.0f,
                        centerPos.y - TILE_SIZE / 2.0f,
                        TILE_SIZE,
                        TILE_SIZE
                    );

                    if (!isOccupied && currentSelection != SelectedTowerType::NONE && !map.isPositionOnPath(proposedBounds))
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
}

float getSpawnIntervalForEnemy(EnemyType type)
{
    if (type == EnemyType::Normal)
    {
        return 0.6f;
    }
    else if (type == EnemyType::Fast)
    {
        return 0.1f;
    }
    else if (type == EnemyType::Tank)
    {
        return 0.8f;
    }

    return 0.6f;
}


void Game::update(float deltaTime)
{
    // ---------------- OBSŁUGA MENU ----------------
    if (State == MenuState::MENU)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (playButtonText.getGlobalBounds().contains(mousePos))
        {
            playButtonText.setFillColor(sf::Color::Green);
        }
        else
        {
            playButtonText.setFillColor(sf::Color::White);
        }

        if (exitButtonText.getGlobalBounds().contains(mousePos))
        {
            exitButtonText.setFillColor(sf::Color::Red);
        }
        else
        {
            exitButtonText.setFillColor(sf::Color::White);
        }

        return;
    }

    if (gameover)
    {
        return;
    }

    if (gameStarted && gameState.currentWave < waves.size())
    {
        if (waveActive)
        {
            spawnTimer += deltaTime;

            if (currentEnemyInWave < waves[gameState.currentWave].size())
            {
                EnemyType enemyType = waves[gameState.currentWave][currentEnemyInWave];

                float currentSpawnInterval = getSpawnIntervalForEnemy(enemyType);

                if (spawnTimer >= currentSpawnInterval)
                {
                    enemies.push_back(Enemy(map.getWaypoints(), enemyType));

                    currentEnemyInWave++;

                    spawnTimer = 0.f;
                }
            }
            else
            {
                waveActive = false;
                waitingForNextWave = true;
            }
        }
        else
        {
            if (enemies.empty() && waitingForNextWave)
            {
               

                gameState.currentWave++;
                currentEnemyInWave = 0;

                gameStarted = false;
                waitingForNextWave = true;
                spawnTimer = 0.f;
            }
        }
    }

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (currentSelection != SelectedTowerType::NONE)
    {
        sf::Vector2f snappedPos = map.snapToGrid(mousePos);
        previewSprite.setPosition(snappedPos);
    }

    for (auto& enemy : enemies)
    {
        enemy.update(deltaTime);
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].reachedEnd())
        {
            if (enemies[i].getType() == EnemyType::Normal)
                gameState.playerHP--;
            if (enemies[i].getType() == EnemyType::Fast)
                gameState.playerHP -= 3;
            if (enemies[i].getType() == EnemyType::Tank)
                gameState.playerHP -= 6;

            enemies.erase(enemies.begin() + i);

            i--;

            if (gameState.playerHP <= 0)
            {
                gameover = true;
                gamewon = false;
                return;
            }
        }
    }

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

    if (gameState.currentWave >= waves.size() && enemies.empty() && gameState.playerHP > 0)
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

    if (hud.getMenuButtonBounds().contains(mousePos))
    {
        hud.setMenuButtonHovered(true);
    }
    else
    {
        hud.setMenuButtonHovered(false);
    }

    hud.update(currentState);
}

void Game::render()
{
    window.clear(sf::Color::Black);

    // --- STAN MENU ---
    if (State == MenuState::MENU)
    {
        
        window.draw(menuBgSprite);
        window.draw(playButtonText);
        window.draw(exitButtonText);
    }
    // --- STAN GRY ---
    else if (State == MenuState::PLAYING)
    {
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

        if (gameover)
        {
            window.draw(winScreen);

            if (gamewon)
            {
                window.draw(winText);
            }
            else
            {
                window.draw(loseText);
            }
        }
    }

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

    previewSprite.setOrigin(
        previewTexture.getSize().x / 2.f,
        previewTexture.getSize().y / 2.f
    );

    float targetSize = 90.f;

    previewSprite.setScale(
        targetSize / previewTexture.getSize().x,
        targetSize / previewTexture.getSize().y
    );
}
    else if (key == sf::Keyboard::Num2)
    {
        currentSelection = SelectedTowerType::MACHINE_GUN;

        previewTexture.loadFromFile("asets/textures/machine2.png");
        previewSprite.setTexture(previewTexture, true);

        previewSprite.setColor(sf::Color(255, 255, 255, 150));

        previewSprite.setOrigin(
            previewTexture.getSize().x / 2.f,
            previewTexture.getSize().y / 2.f
        );

        float targetSize = 90.f;

        previewSprite.setScale(
            targetSize / previewTexture.getSize().x,
            targetSize / previewTexture.getSize().y
        );
    }

    else if (key == sf::Keyboard::Num3)
{
    currentSelection = SelectedTowerType::SHOT_GUN;

    previewTexture.loadFromFile("asets/textures/shot2.png");
    previewSprite.setTexture(previewTexture, true);

    previewSprite.setColor(sf::Color(255, 255, 255, 150));

    previewSprite.setOrigin(
        previewTexture.getSize().x / 2.f,
        previewTexture.getSize().y / 2.f
    );

    float targetSize = 90.f;

    previewSprite.setScale(
        targetSize / previewTexture.getSize().x,
        targetSize / previewTexture.getSize().y
    );
}
    else if (key == sf::Keyboard::Escape)
    {
        currentSelection = SelectedTowerType::NONE;
    }
    else if (key == sf::Keyboard::Enter)
    {
        if (waitingForNextWave && gameState.currentWave < waves.size())
        {
            gameStarted = true;
            waitingForNextWave = false;
            waveActive = true;
            spawnTimer = 0.f;
        }
    }
    else if (key == sf::Keyboard::F1)
    {
        gameover = true;
        gamewon = true;
    }
    else if (key == sf::Keyboard::F2)
    {
        gameover = true;
        gamewon = false;
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
    addEnemiesToWave(wave2, Normal, 25);
    newWaves.push_back(wave2);

    vector<EnemyType> wave3;
    addEnemiesToWave(wave3, Normal, 10);
    addEnemiesToWave(wave3, Fast, 5);
    addEnemiesToWave(wave3, Normal, 10);
    addEnemiesToWave(wave3, Fast, 5);
    addEnemiesToWave(wave3, Normal, 10);
    addEnemiesToWave(wave3, Fast, 5);
    newWaves.push_back(wave3);

    vector<EnemyType> wave4;
    addEnemiesToWave(wave4, Normal, 25);
    addEnemiesToWave(wave4, Fast, 25);
    addEnemiesToWave(wave4, Tank, 5);
    newWaves.push_back(wave4);

    vector<EnemyType> wave5;
    addEnemiesToWave(wave5, Normal, 25);
    addEnemiesToWave(wave5, Fast, 20);
    addEnemiesToWave(wave5, Tank, 15);
    newWaves.push_back(wave5);

    vector<EnemyType> wave6;
    addEnemiesToWave(wave6, Normal, 15);
    addEnemiesToWave(wave6, Fast, 15);
    addEnemiesToWave(wave6, Normal, 15);
    addEnemiesToWave(wave6, Tank, 10);
    newWaves.push_back(wave6);

    vector<EnemyType> wave7;
    addEnemiesToWave(wave7, Normal, 20);
    addEnemiesToWave(wave7, Fast, 20);
    addEnemiesToWave(wave7, Normal, 15);
    addEnemiesToWave(wave7, Tank, 15);
    newWaves.push_back(wave7);

    vector<EnemyType> wave8;
    addEnemiesToWave(wave8, Normal, 20);
    addEnemiesToWave(wave8, Fast, 20);
    addEnemiesToWave(wave8, Tank, 10);
    addEnemiesToWave(wave8, Normal, 15);
    addEnemiesToWave(wave8, Tank, 10);
    addEnemiesToWave(wave8, Fast, 20);
    addEnemiesToWave(wave8, Normal, 50);
    newWaves.push_back(wave8);

    return newWaves;
}
