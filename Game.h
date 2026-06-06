#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tower.h"
#include "enemy.h"
#include "Projectile.h"
#include "Map.h"
class Game {
private:
    sf::RenderWindow window;

    Map map;
    int money; 
    int playerHp;
    bool gameover;
    bool gamewon;
    enum class GameMode {easy,medium,hard};
    GameMode gamemode;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Tower>> towers;

    enum class SelectedTowerType { NONE, SNIPER, MACHINE_GUN, SHOT_GUN };
    SelectedTowerType currentSelection;

    
    sf::Texture previewTexture;
    sf::Sprite previewSprite;
    float spawnTimer;
    float spawnInterval;
   
    void processEvents();
    void handleKeyPress(sf::Keyboard::Key key);
    void update(float deltaTime);
    void render();
    vector<vector<EnemyType>>createWaves();
    //fale przeciwnikow
    vector<vector<EnemyType>> waves;
int currentWave;
int currentEnemyInWave;
bool waveActive;
float timeBetweenWaves;
float waveBreakTimer;

public:
    Game();
    void run();
};

