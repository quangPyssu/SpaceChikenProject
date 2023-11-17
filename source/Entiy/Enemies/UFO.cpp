#include "../Enemy.h"

UFO::UFO(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);
	
	animations.push_back(new Animation(5,10, 1, 1, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "UFO.png"));
	
	animations.back()->PushToObject(animations.back(), this);

	setHitBox(animations.back()->getSize()*0.7);	

	HitPoints = HitPointsMax = 2500;

	ApplyPhysics();
	Velocity = { 50,20 };
	Acceleration = { 0,0 };

	reloadFrameID = 125;
	reloadFrameIDMax = 125;

	attackTypeMax = 1;

	type = EnemyType_UFO;
}

void UFO::addDeathAnimation()
{
	Entity::addDeathAnimation();

	animations.push_back(new Animation(10, 8, 1, 5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("(chickbossDie).ogg");	
}

void UFO::attack()
{
	switch (attackType)
	{
		case 0:
			EnimesBullets->addBullet(BulletType::BulletType_Enemy_Purple, getPosition());
		break;

		case 1:
			EnimesBullets->addBullet(BulletType::BulletType_Enemy_Purple, getPosition());
			//EnimesBullets->addBullet(BulletType::BulletType_Enemy_Purple, getPosition());
		break;

		default:
			break;
	}
}

void UFO::atHalfHealth()
{
	//explosions
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("(chickbossCry).ogg");
	attackTypeMax =2;

	
	isFiring = true;

	gotoPosition( Vector2f(WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 4));
}

void UFO::atQuarterHealth()
{
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	isFiring = true;

	gotoPosition(Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 4));
}