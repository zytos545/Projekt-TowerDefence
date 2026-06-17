#pragma once

#include <SFML/Graphics.hpp>
#include "HUD.h"
#include <vector>
#include <memory>
#include "Tower.h"
#include "GameState.h"
#include "enemy.h"
#include "Projectile.h"
#include "Map.h"
class Game {
private:
    enum class MenuState { MENU, PLAYING };
    MenuState State;

    
    sf::Font menuFont;
    sf::Text playButtonText;
    sf::RenderWindow window;
    Map map;
    GameState gameState;
    bool gameover;
    bool gamewon;
    bool gameStarted;
    bool waitingForNextWave;
    sf::RectangleShape winScreen;
    sf::Font winFont;
    sf::Text winText;
    sf::Text loseText;
    enum class GameMode {easy,medium,hard};
    GameMode gamemode;
    HUD hud;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Tower>> towers;
    float spawnTimer;
    float spawnInterval;
    enum class SelectedTowerType { NONE, SNIPER, MACHINE_GUN, SHOT_GUN };
    SelectedTowerType currentSelection;
   

    sf::Texture previewTexture;
    sf::Sprite previewSprite;

    void processEvents();
    void handleKeyPress(sf::Keyboard::Key key);
    void update(float deltaTime);
    void render();
    vector<vector<EnemyType>>createWaves();
    vector<vector<EnemyType>> waves;
    int currentEnemyInWave;
    bool waveActive;
    float timeBetweenWaves;
    float waveBreakTimer;

public:
    Game();
    void run();
};

