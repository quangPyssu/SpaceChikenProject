#pragma once
#include "../SceneNode.h"

class Entity : public SceneNode
{
public:
    Entity();


    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateCurrent(sf::Event& event, sf::Vector2f& MousePos) override;

 
    void takeTimeCurrent(sf::Time& dt) override;

};

