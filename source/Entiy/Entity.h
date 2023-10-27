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

    void setRootPos(Vector2f& rootPos);

    EntityState CurrentEnityState = EntityState::Alive;

    void killEntity();

    void setDivation(Vector2f divation);

    //int HitPoints = 1;
    bool rotationDependent = false;
    float RotationDivation = 0;

protected:
    Vector2f Velocity = { 0,0 };
    Vector2f Acceleration = { 0,0 };

    Vector2f* RootPos = nullptr;
    Vector2f Divation = { 0,0 };


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

    int timerStart = 0, timerEnd = -1;
    void setTimer(int timerStart,int timerEnd);
    

protected:
    bool Destructible = true;
   
    void outScope(); //check if the entity is out of the screen 

    bool CollitionDetection(const Entity& other);

    RectangleShape hitbox;

    friend class BulletManager;
    friend class pattern;
};

