#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core/Global.h"
#include <cassert>


using namespace sf;
using namespace std;
using namespace Colors;
using namespace Constants;
using namespace utility;


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

    void takeTime();

    virtual void takeTimeCurrent() {};

    void PushToObject(SceneNode* tmp, SceneNode* Father);

    int getTimerStart() { return timerStart; }

public:
    vector<Ptr> Children;
    SceneNode* Parent=nullptr;

    bool isDisable = false;
    bool isInteractable = false;

    virtual void Disable();
    virtual void Able();

    bool rotationDependent = false;
    float RotationDivation = 0;

protected:
    int timerStart = 0;
};

