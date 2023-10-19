#pragma once

#include "SceneNode.h"

class Button : public SceneNode
{
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text);
    Button(const sf::Vector2f& position, int ButtonType, const std::string& text);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;
    void takeTimeCurrent() override;

    bool isLeftClicked(Event& event, Vector2f& MousePos);
    bool isRightClicked(Event& event, Vector2f& MousePos);
    bool isHovered(Event& event, Vector2f& MousePos);

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Texture texture;
};

