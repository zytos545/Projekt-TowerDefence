#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "HUD.h"
#include "Tower.h"
#include "GameState.h"
#include "enemy.h"
#include "Projectile.h"
#include "Map.h"

class Game {
private:
    sf::RenderWindow window;

    Map map;
    HUD hud;
    GameState gameState;

    enum class MenuState { MENU, PLAYING };
    MenuState State;

    enum class GameMode { easy, medium, hard };
    GameMode gamemode;

    enum class SelectedTowerType { NONE, SNIPER, MACHINE_GUN, SHOT_GUN };
    SelectedTowerType currentSelection;

    bool gameover;
    bool gamewon;
    bool gameStarted;
    bool waitingForNextWave;

    // menu
    sf::Texture menuBgTexture;
    sf::Sprite menuBgSprite;
    sf::Font menuFont;
    sf::Text playButtonText;
    sf::Text exitButtonText;

    bool showControls = false;
    sf::Text controlsButtonText;
    sf::Text instructionsText;
    sf::Text backButtonText;

    // muzyka
    sf::Music backgroundMusic;

    sf::Texture winTexture;
    sf::Sprite winSprite;

    sf::Texture loseTexture;
    sf::Sprite loseSprite;

    sf::RectangleShape winScreen;
    sf::Font winFont;
    sf::Text winText;
    sf::Text loseText;

    // obiekty gry
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Tower>> towers;

    // podgl¹d wie¿yczki
    sf::Texture previewTexture;
    sf::Sprite previewSprite;

    // fale
    std::vector<std::vector<EnemyType>> waves;
    int currentEnemyInWave;
    bool waveActive;
    float spawnTimer;
    float spawnInterval;
    float timeBetweenWaves;
    float waveBreakTimer;

    void processEvents();
    void handleKeyPress(sf::Keyboard::Key key);
    void update(float deltaTime);
    void render();

    std::vector<std::vector<EnemyType>> createWaves();

public:
    Game();
    void run();
};