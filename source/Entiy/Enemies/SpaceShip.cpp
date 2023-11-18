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

	animations.push_back(new Animation(20, 8, 1, 1, { 0,0 }, { 0.5,0.6 }, Vector2f(0, 0), "Battlecruiser_Engine.png"));
	animations.back()->setRotationDivation(180);
	animations.back()->setScale({ 0.8,1.4 });
	animations.back()->PushToObject(animations.back(), this);
	

	setHitBox(sprites.back()->getSize()*0.8);	

	HitPoints = HitPointsMax = 2500;

	ApplyPhysics();
	Velocity = { 50,20 };
	Acceleration = { 0,0 };

	reloadFrameID = 125;
	reloadFrameIDMax = 125;

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
	switch (attackType)
	{
		case 0:
			EnimesBullets->addBullet(BulletType::BulletType_Enemy_Purple, getPosition());
		break;

		default:
			break;
	}
}

void SpaceShip::atThreeQuarterHealth()
{

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

	reloadFrameID = 100;
	reloadFrameIDMax = 100;
	
	isFiring = true;

	gotoPosition( Vector2f(WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 4));
}

void SpaceShip::atQuarterHealth()
{
	animations.push_back(new Animation(10, 8, 1, 1.5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	reloadFrameID = 90;
	reloadFrameIDMax = 90;
	isFiring = true;

	gotoPosition(Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 4));
	playSound("PlayerExplode.ogg");
}

void SpaceShip::additionalBehavior()
{
	if (!isRamming)	
		gotoPosition(Vector2f(player->getPosition().x, getPosition().y),170);
}

