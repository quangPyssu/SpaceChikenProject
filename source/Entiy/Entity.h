#pragma once
#include "../SceneNode.h"
#include "../Animation/Animation.h"

class Entity : public SceneNode
{
public:
    Entity();


    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateCurrent(sf::Event& event, sf::Vector2f& MousePos) override;

    void takeTimeCurrent() override;

    void setVelocity(sf::Vector2f velocity);

    void setAcceleration(sf::Vector2f acceleration);

protected:
    Vector2f Velocity;
    Vector2f Acceleration;

    vector<Animation*> animations;
    vector<Sprite*> sprites;
};

