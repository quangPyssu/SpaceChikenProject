#pragma once

#include "State.h"
#include "../Entiy/Player.h"
#include "../Entiy/Enemy.h"
#include "../Tools/BulletManager.h"

class GameState: public State
{
public:
    GameState();
    ~GameState();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;
    void takeTimeCurrent() override;

private:

    sf::Texture textureBack;

    sf::Sprite backgroundSprite;


    // Player, Enimes, 

    Player* player;
    vector <Enemy*> enemy;

    BulletManager* PlayerBullets_Standard;
    BulletManager* PlayerBullets_Detroyer;
    BulletManager* EnimesBullets;    
};

