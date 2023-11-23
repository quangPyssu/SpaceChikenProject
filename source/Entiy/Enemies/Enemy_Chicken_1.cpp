#include "../Enemy.h"

Enemy_Chicken_1::Enemy_Chicken_1(Vector2f StartPosition) : Enemy(StartPosition)
{	
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);	

	animations.push_back(new Animation(2, 50, 1, 0.35, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "ChickenBody.png"));
	animations.back()->makePingPong();
	animations.back()->PushToObject(animations.back(), this);

	animations.push_back(new Animation(20, 25, 1, 1, { 0,0 }, { 0.5,1 }, Vector2f(0, 0), "ChickenFace.png"));
	animations.back()->setCurrentFrame(rand() % 25);
	animations.back()->makePingPong();
	animations.back()->PushToObject(animations.back(), this);

	setHitBox(animations[0]->getSize()*0.7);	

	HitPoints = HitPointsMax = 60;

	ApplyPhysics();
	Velocity = { 50,(float)0 + rand() % 20 + 10 };
	Acceleration = { 0,0 };

	reloadFrameID = rand() % 300;
	reloadFrameIDMax = 350;

	attackTypeMax = 1;	

	type = EnemyType_Chicken_1;
}

void Enemy_Chicken_1::addDeathAnimation()
{
	Entity::addDeathAnimation();	

	animations.push_back(new Animation(10, 8, 1, 1.2, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("chicken1a(die).ogg");			
}

void Enemy_Chicken_1::attack()
{
	EnimesBullets->addBullet(BulletType::BulletType_Enemy_Egg, getPosition());
}