#include "../Enemy.h"

SpaceShip::SpaceShip(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);

	sprites.push_back(new SpriteOnly("space_ship.png", Vector2f(0, 0)));
	sprites.back()->setOrigin({ 0.5,0.5 });
	sprites.back()->setScale(0.5);
	sprites.back()->PushToObject(sprites.back(), this);

	setHitBox(sprites.back()->getSize() * 0.8);

	animations.push_back(new Animation(20, 8, 1, 1, { 0,0 }, { 0.5,0.6 }, Vector2f(0, 0), "Battlecruiser_Engine.png"));
	animations.back()->setRotationDivation(180);
	animations.back()->setScale({ 0.8,1.4 });
	animations.back()->PushToObject(animations.back(), this);	

	HitPoints = HitPointsMax = 2200;
	if (CurrentLevel == 4) HitPoints = 1300;

	Velocity = { 50,20 };
	Acceleration = { 0,0 };

	reloadFrameID = 90;
	reloadFrameIDMax = 90;

	attackTypeMax = 1;

	type = EnemyType_SpaceShip;

	playSpawnSound("(ufoEngine).ogg");
	sounds.back()->setLoop(1);
}

void SpaceShip::addDeathAnimation()
{
	Entity::addDeathAnimation();

	animations.push_back(new Animation(10, 8, 1, 5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("PlayerExplode.ogg");	
}

void SpaceShip::attack()
{
	if (!isRamming)
	{
		addSpaceShipBullet(true);
	}
	else
	{
		switch (attackTypeMax)
		{
		case 1:
			{
				for (int i = 0; i < 5; i++)	addSpaceShipBullet(true);
			}
			break;

		case 2:
			{
				for (int i = 0; i < 5; i++) addSpaceShipBullet(false);
			}
			break;

		case 3:
		{
			for (int i = 0; i < 5; i++)
			{
				addSpaceShipBullet(false);
			}
		}
		break;
		}
		
	}
}

void SpaceShip::atThreeQuarterHealth()
{
	reloadFrameID = 75;
	reloadFrameIDMax = 75;

	isRamming = 1000;
	RammingSpeed = 200;
	ramming();
	
}

void SpaceShip::atHalfHealth()
{
	//explosions
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	sounds.back()->setLoop(0);
	sounds.back()->stop();
	playSound("engineUfoDamaged.ogg");
	sounds.back()->setLoop(1);

	playSound("PlayerExplode.ogg");

	reloadFrameID = 50;
	reloadFrameIDMax = 50;
	attackTypeMax = 2;

	isRamming = 1200;
	RammingSpeed = 300;
	ramming();
}

void SpaceShip::atQuarterHealth()
{
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	playSound("PlayerExplode.ogg");
	attackTypeMax = 3;

	isRamming = 1500;
	RammingSpeed = 400;
	ramming();
}

void SpaceShip::additionalBehavior()
{
	if (!isRamming)	gotoPosition(Vector2f(player->getPosition().x, 100*SCALE),170); else
	{
		if (isRamming > 0)
		{
			isRamming--;
			if (!isGoingToPos)
			{
				setPosition(Vector2f(player->getPosition().x, -200));
				ramming();
			}
		}
		else isRamming = 0;
	}	
}

void SpaceShip::ramming()
{
	setPosition(Vector2f(player->getPosition().x, getPosition().y));
	gotoPosition(Vector2f(player->getPosition().x, WINDOW_SIZE.y + 150 * SCALE), RammingSpeed*SCALE);
	EnimesBullets->addBullet(BulletType_Enemy_Ram_Destroyer, getPosition() + Vector2f(0, 0));
	EnimesBullets->setBulletBackVelocity(Vector2f( 0, RammingSpeed*SCALE ));
	EnimesBullets->setBulletBackTimerEnd(isRamming);
}

void SpaceShip::addSpaceShipBullet(bool isRotated)
{
	EnimesBullets->addBullet(BulletType::BulletType_Player_Minigun, getPosition());
	EnimesBullets->setBulletBackDamage(30);
	
	if (isRotated) EnimesBullets->reverseBulletBackDirection();
}
