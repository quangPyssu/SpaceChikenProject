#pragma once

#include "SceneNode.h"
#include "Animation/SpriteOnly.h"

class Button : public SceneNode
{
public:
    Button(const sf::Vector2f position, const sf::Vector2f& size, const std::string& text);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(Event& event, Vector2f& MousePos) override;

    bool isLeftClicked(Event& event, Vector2f& MousePos);
    bool isRightClicked(Event& event, Vector2f& MousePos);
    bool isHovered(Event& event, Vector2f& MousePos);

    Vector2f getSize() { return shape.getSize(); }
    void setSize(const Vector2f& size) { setSize(size); shape.setSize(size); }

    Vector2f getPosition() {return  shape.getPosition(); }
    void setPosition(const Vector2f& position) { setPosition(position); shape.setPosition(position); }

    void setSpriteOnly(const std::string& textureName);

private:
    sf::RectangleShape shape;
    sf::Text label;
    SpriteOnly* sprite=nullptr;
};

