#pragma once

#include "../SceneNode.h"

class SubTitle : public SceneNode
{
public:
    SubTitle(sf::Vector2f position, sf::Vector2f size, sf::Color bgColor,
        sf::Vector2f labelPos,int labelSize, sf::Color labelColor, std::string label,std::string font,int timerEnd);
~SubTitle();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void takeTimeCurrent() override;
    
    bool isDead() { return !timerEnd; }

private:
    sf::RectangleShape background;
    sf::Text label;

    float totalWidth;
    float totalHeight;    

    float baseBGAlpha = 255;
    float baseLabelAlpha = 255;

    void setTranparency(float alpha);
    int timerEndBase=1;
    int timerEnd;
};

