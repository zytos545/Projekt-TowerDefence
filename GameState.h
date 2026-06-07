#pragma once
#include <string>

struct GameState {
    int money = 0;
    int playerHP = 0;
    int currentWave = 0;
    int upgradeCost = 0;
    int expe = 0;
    std::string towerName = "";
    bool isUpgrade = false;
};