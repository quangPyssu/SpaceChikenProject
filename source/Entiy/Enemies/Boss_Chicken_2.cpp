#include "../Enemy.h"

Boss_Chicken_2::Boss_Chicken_2(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);
	
	animations.push_back(new Animation(2, 50, 1, 0.75, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "ChickenBody.png"));
	animations.back()->makePingPong();
	animations.back()->PushToObject(animations.back(), this);

	sprites.push_back(new SpriteOnly("SuperHenBody2.png", Vector2f(0, 0)));
	sprites.back()->setScale(0.4);
	sprites.back()->setOrigin({ 0.5,0.68 });
	sprites.back()->PushToObject(sprites.back(), this);

	setHitBox(animations.back()->getSize()*0.7);	

	HitPoints = HitPointsMax = 4000;

	ApplyPhysics();
	Velocity = { 50,0 };
	Acceleration = { 0,-1 };

	reloadFrameID = 420;
	reloadFrameIDMax = 420;

	attackTypeMax = 1;

	type = EnemyType_Boss_Chicken_2;
}

void Boss_Chicken_2::addDeathAnimation()
{
	Entity::addDeathAnimation();

	animations.push_back(new Animation(10, 8, 1, 5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("(chickbossDie).ogg");	
}

void Boss_Chicken_2::attack()
{
	switch (attackType)
	{
	case 0: // 2 Circle aim for player
	{
		for (int j = 0; j < 2; j++)
		{
			BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::Spin, *EnimesBullets,
				getPosition(), { 0,0 }, { 0,0 }, false, 10, 40*SCALE, 0, *warningZone, j * 100, 2000, 1);

			Enemy_BulletPattern_queue.push({ tmp,5 });
		}
	}
	break;

	case 1: // 3 firework
	{
		FireworkAttack();
	}
	break;
	}
}

void Boss_Chicken_2::atThreeQuarterHealth()
{
	SpawnType = EnemyType_BlackHole; 
	spawnRequest = true;
	playSound("(chickbossDie).ogg");

	gotoPosition(Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 4));
	FireworkAttack();
	attackTypeMax = 2;
}

void Boss_Chicken_2::atHalfHealth()
{
	SpawnType = EnemyType_SemiVortex;
	spawnRequest = true;

	//explosions
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 200));
	PushToObject(animations.back(), this);

	playSound("(chickbossCry).ogg");	
	

	gotoPosition( Vector2f(WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 4));
	FireworkAttack();
}

void Boss_Chicken_2::atQuarterHealth()
{
	SpawnType = EnemyType_SprialVortex;
	spawnRequest = true;

	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 200));
	PushToObject(animations.back(), this);

	playSound("(chickbossCry).ogg");

	gotoPosition(Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 4));
	FireworkAttack();
}

void Boss_Chicken_2::FireworkAttack() 
{
	for (int j = 0; j < 3; j++)
	{
		BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Firework, RotationType::defaultRotation, *EnimesBullets,
			getPosition(), Vector2f(60,60)*SCALE, { 0,0 }, false, 10, 100 * SCALE, 5, *warningZone, j * 100, 2000, 1);

		Enemy_BulletPattern_queue.push({ tmp,0 });
	}
	isFiring = true;
}