#pragma once

#include "State.h"

class MainMenu : public State
{
public:
    MainMenu();
    ~MainMenu();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;
    void takeTimeCurrent() override;

private:

    sf::Texture textureBack;

    sf::Sprite backgroundSprite;
    sf::Sprite CursorSprite;

    Animation* animePlanetTop;
    Animation* animeNeutronStar;

    Button* btn_Continue=nullptr;
    Button* btn_Quit=nullptr;
    Button* btn_NewGame=nullptr;
    Button* btn_Load=nullptr;
    Button* btn_Setting=nullptr;
};

