#pragma once

#include "State.h"
#include "../Entiy/Player.h"
#include "../Entiy/Enemy.h"
#include "../Tools/BulletManager.h"
#include "../Tools/ProgressBar.h"
#include "../Tools/EnemyManager.h"
#include "../Entiy/BulletPattern.h"
#include "../Entiy/EnemyPattern.h"
#include "../Tools/LevelReader.h"
#include "../Animation/WarningZone.h"
#include "GameOverScreen.h"


class GameState: public State
{
public:
    GameState(State& parentState,RenderWindow& window);
    ~GameState();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;
    void takeTimeCurrent() override;

private:

    sf::Texture textureBack;

    sf::Sprite backgroundSprite;

    LevelReader levelReader;


    // Player, Enimes, 

    Player* player;

    BulletManager* PlayerBullets_Standard;
    BulletManager* PlayerBullets_Detroyer;
    BulletManager* EnimesBullets;   
    BulletManager* EnimesBullets_Vulnerable;
    BulletManager* EnimesBullets_Indestructible;

    EnemyManager* enemyManager;

    vector <BulletPattern*> BulletPatternList;
    vector <EnemyPattern*> EnemyPatternList;    

    void addEnemyPattern(EnemyPatternType type, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, 
        int total, float width, int widthCnt);
    void addBulletPattern(BulletPatternType type, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, 
        int total, float width, int widthCnt,int timerStart,int timerEnd);

    void readAttackQueue();
    void readWaveQueue();

    void BGLoop();

    bool isWaveEmpty();

    // UI
    ProgressBar* PBplayerHealth;

    WarningZone* warningZone;


    bool wasPaused = false;

    //data
    float scrollSpeed = 25.0f;
    float BGHeight = 0.0f;
};

