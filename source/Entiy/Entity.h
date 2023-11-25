#pragma once
#include "../SceneNode.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"
#include "../Animation/Flicker.h"

enum EntityState { Alive = 0, Dying = 1, Dead = 2 };

class Entity : public SceneNode, protected Flicker
{

public:
    //static int EntityCount;

   // Entity();
    ~Entity();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void takeTimeCurrent() override;

    void setVelocity(sf::Vector2f velocity);

    void setAcceleration(sf::Vector2f acceleration);

    void ApplyPhysics();

    void setRootPos(Vector2f& rootPos);

    void setPosition(Vector2f position);

    void setTimer(int timerStart, int timerEnd);

    void setHitBox(Vector2f size);

    int getHitPoint() { return HitPoints; };
    void setHitPoints(int HitPoints){ this->HitPoints = HitPoints;  };

    void gotoPosition(Vector2f Position,float speed=100);

    EntityState CurrentEnityState = EntityState::Alive;

    void killEntity();

    void setDivation(Vector2f divation);

    Vector2f getVelocity();

    //int HitPoints = 1;
    bool rotationDependent = false;
    float RotationDivation = 0;
    float baseRotation = 0;

    void setBaseRotation(float rotation);

    float angleToB(Entity* B);
    float angleToB(Vector2f posB);
    Vector2f velocityToB(double baseVelocity, Entity* B);
    Vector2f velocityToB(double baseVelocity, Vector2f posB);

    Vector2f AngleShift(Vector2f vec, double angle);

protected:
    Vector2f Velocity = { 0,0 };
    Vector2f Acceleration = { 0,0 };

    Vector2f VelocitySave = { 0,0 };
    Vector2f AccelerationSave = { 0,0 };
    Vector2f CurrentDestination = { 0,0 };
    bool isGoingToPos = false;

    Vector2f* RootPos = nullptr;
    Vector2f Divation = { 0,0 };


    virtual void addDeathAnimation();

    vector <Animation*> animations;
    vector <SpriteOnly*> sprites;
    vector <Sound*> sounds;

    void CleanDeadAssets();

    void takeTimeFlicker() override;

protected:

    enum damageEvent { NoDamage = 0, TakeDamage = 1, HalfHealth = 2, QuarterHealth = 3,ThreeQuarterHealth=4 };

    int HitPoints = 1;
    int HitPointsMax = 1;
    int Damage = 0;


    bool isFirstTime = true;
    bool hasPhysics = false;
    bool isInvincibleWhenFlicker = false;

    damageEvent takeDamage(int damage);
    virtual void atThreeQuarterHealth() {};
    virtual void atHalfHealth() {};
    virtual void atQuarterHealth() {};

    void playSound(string soundName);
    void playSpawnSound(string soundName);

    int timerEnd = -1;    
    

protected:
    bool Destructible = true;
   
    void outScope(); //check if the entity is out of the screen 

    bool CollitionDetection(const Entity& other);

    RectangleShape hitbox;

    friend class BulletManager;
    friend class pattern;
};

