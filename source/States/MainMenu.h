#pragma once

#include "State.h"

class MainMenu : public State
{
public:
    MainMenu();
    ~MainMenu();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;
    void takeTimeCurrent(Time& dt) override;

private:
    sf::Texture texture;
    sf::Texture textureBack;

    sf::Sprite backgroundSprite;
    Button* btn_Quit;
    Button* btn_NewGame;
    Button* btn_Load;
    Button* btn_HighScore;
    Button* btn_Play;
    Button* btn_Setting;
};

