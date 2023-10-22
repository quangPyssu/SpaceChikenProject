#pragma once
#include "../SceneNode.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"

class Entity : public SceneNode
{
public:

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void takeTimeCurrent() override;

    void setVelocity(sf::Vector2f velocity);

    void setAcceleration(sf::Vector2f acceleration);  

    void ApplyPhysics();

    bool isDead = false;

protected:
    Vector2f Velocity = { 0,0 };
    Vector2f Acceleration = { 0,0 };
    Vector2f D_Acceleration = { 0,0 };


    vector <Animation*> animations;
    vector <SpriteOnly*> sprites;

protected:

    int HitPoints = 1;
    int Damage = 0;    

    bool hasPhysics = false;

    void takeDamage(int damage);

protected:
   
    void outScope(); //check if the entity is out of the screen 

    bool CollitionDetection(const Entity& other);

    RectangleShape hitbox;

    friend class BulletManager;
};

