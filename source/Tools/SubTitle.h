#pragma once

#include "../SceneNode.h"

class ProgressBar : public SceneNode
{
public:
    ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color bgColor, std::string name, int& Base, int& BaseMax);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void takeTimeCurrent() override;

private:
    sf::RectangleShape background;
    sf::RectangleShape bar;
    sf::Text label;
    float totalWidth;
    float totalHeight;

    int* Base = null;
    int* BaseMax = null;
};

