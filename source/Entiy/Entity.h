#pragma once
#include "../SceneNode.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"

enum EntityState { Alive = 0, Dying = 1, Dead = 2 };

class Entity : public SceneNode
{   

public:
    ~Entity();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void takeTimeCurrent() override;

    void setVelocity(sf::Vector2f velocity);

    void setAcceleration(sf::Vector2f acceleration);  

    void ApplyPhysics();

    EntityState CurrentEnityState = EntityState::Alive;

    //int HitPoints = 1;

protected:
    Vector2f Velocity = { 0,0 };
    Vector2f Acceleration = { 0,0 };
    Vector2f D_Acceleration = { 0,0 };
    virtual void addDeathAnimation();


    vector <Animation*> animations;
    vector <SpriteOnly*> sprites;
    vector <Sound*> sounds;

    void CleanDeadAssets();


protected:

    int HitPoints = 1;
    int Damage = 0;    

    bool hasPhysics = false;

    void takeDamage(int damage);
    void playSound(string soundName);

protected:
   
    void outScope(); //check if the entity is out of the screen 

    bool CollitionDetection(const Entity& other);

    RectangleShape hitbox;

    friend class BulletManager;
};

