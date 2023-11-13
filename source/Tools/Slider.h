#pragma once

#include "../SceneNode.h"

class Slider : public SceneNode
{
public:
    Slider(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color bgColor, std::string name, int& Base, int BaseMax);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;

private:
    sf::RectangleShape background;
    sf::RectangleShape bar;
    sf::Text label;
    sf::Text percent;

    float totalWidth;
    float totalHeight;

    int* Base = null;
    int BaseMax = 1;

    bool isPressed = false;
};

