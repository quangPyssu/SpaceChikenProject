#include "../Enemy.h"

Boss_Chicken_1::Boss_Chicken_1(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);
	hitbox.setSize({ 112,112 });
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

	animations.push_back(new Animation(2, 50, 1, 0.75, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "ChickenBody.png"));
	animations.back()->makePingPong();
	animations.back()->PushToObject(animations.back(), this);

	sprites.push_back(new SpriteOnly("BossChickenBody.png", Vector2f(0, 0)));
	sprites.back()->setOrigin({ 0.5,0.68 });
	sprites.back()->PushToObject(sprites.back(), this);

	HitPoints = HitPointsMax = 2500;

	ApplyPhysics();
	Velocity = { 50,20 };
	Acceleration = { 0,-1 };

	reloadFrameID = 420;
	reloadFrameIDMax = 420;

	attackTypeMax = 2;

	type = EnemyType_Boss_Chicken_1;
}

void Boss_Chicken_1::addDeathAnimation()
{
	Entity::addDeathAnimation();

	animations.push_back(new Animation(10, 8, 1, 5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("(chickbossDie).ogg");	
}

void Boss_Chicken_1::attack()
{
	switch (attackType)
	{
		//new BulletPattern(type, patternType, rotationType, *tmp, Position, Velocity, Acceleration, Physics, total, width, widthCnt, *warningZone, timerStart, timerEnd, thisScale));
	case 0: // barrage
	{
		for (int j = 0; j < 10; j++)
		{
			 BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::defaultRotation, *EnimesBullets, 
				 getPosition(), { 0,0 }, { 0,0 }, false, 1, 0, 1,*warningZone, j * 15, 2000, 1);
			 tmp->setRotation(90);

			 Enemy_BulletPattern_queue.push({ tmp,10 });
		}
	}
	break;

	case 1: // 2 Square
	{
		for (int j = 0; j < 2; j++)
		{
			BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Square, RotationType::defaultRotation, *EnimesBullets,
								getPosition(), { 0,0 }, { 0,0 }, false, 9,75,3, *warningZone, j * 100, 2000, 1);

			Enemy_BulletPattern_queue.push({ tmp,5 });
		}
	}
	break;

	case 2: //4 Direction Circle
	{
		for (int j = 0; j < 4; j++)
		{
			BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::Spin, *EnimesBullets,
								getPosition(), AngleShift(velocityToB(150, player), 90 * j), { 0,0 }, true, 6, 80, 4, *warningZone, 0, 2000, 1);

			Enemy_BulletPattern_queue.push({ tmp,0 });
		}

		//spawn 4 go in 4 direction
	}
	break;

	case 3: // 3 circle
	{
		for (int j = 0; j < 3; j++)
		{
			BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::Spin, *EnimesBullets,
												getPosition(), { 0,0 }, { 0,0 }, false, 10, 70, 0, *warningZone, j * 100, 2000, 1);

			Enemy_BulletPattern_queue.push({ tmp,5 });
		}
	}
	break;
	}
}

void Boss_Chicken_1::atHalfHealth()
{
	detachChild(*sprites[0]);
	sprites.erase(sprites.begin());

	sprites.push_back(new SpriteOnly("BossChickenBody2.png", Vector2f(0, 0)));
	sprites.back()->setOrigin({ 0.5,0.68 });
	sprites.back()->PushToObject(sprites.back(), this);

	//explosions
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("(chickbossCry).ogg");
	attackTypeMax = 4;

	for (int j = 0; j < 4; j++)
	{
		BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::Spin, *EnimesBullets,
			getPosition(), AngleShift(velocityToB(150, player), 90 * j), { 0,0 }, true, 6, 80, 4, *warningZone, 0, 2000, 1);

		Enemy_BulletPattern_queue.push({ tmp,0 });
	}
	
	isFiring = true;
}

void Boss_Chicken_1::atQuarterHealth()
{
	detachChild(*sprites[0]);
	sprites.erase(sprites.begin());

	sprites.push_back(new SpriteOnly("BossChickenBody3.png", Vector2f(0, 0)));
	sprites.back()->setOrigin({ 0.5,0.68 });
	sprites.back()->PushToObject(sprites.back(), this);

	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("(chickbossCry).ogg");

	for (int j = 0; j < 4; j++)
	{
		BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::Spin, *EnimesBullets,
			getPosition(), AngleShift(velocityToB(150, player), 45 * j), { 0,0 }, true, 6, 80, 4, *warningZone, 0, 2000, 1);

		Enemy_BulletPattern_queue.push({ tmp,0 });
	}

	isFiring = true;
}