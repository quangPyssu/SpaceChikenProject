#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core/Global.h"


using namespace sf;
using namespace std;
using namespace Colors;
using namespace Constants;


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::shared_ptr<SceneNode> Ptr;
public:

    void attachChild(Ptr child);

    Ptr detachChild(const SceneNode& node);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

    void update(Event& event, Vector2f& MousePos);

    virtual void updateCurrent(Event& event, Vector2f& MousePos) {};

    void takeTime(Time& dt);

    virtual void takeTimeCurrent(Time& dt) {};

    void PushToObject(SceneNode* tmp, SceneNode* Father);

public:
    vector<Ptr> Children;
    SceneNode* Parent=nullptr;

    bool isDisable = false;
    bool isInteractable = false;

    virtual void Disable();
    virtual void Able();

    virtual void setPosition(SceneNode* other);
};

