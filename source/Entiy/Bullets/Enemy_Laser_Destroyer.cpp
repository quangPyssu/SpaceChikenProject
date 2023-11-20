#include "../Bullet.h"

Enemy_Laser_Destroyer::Enemy_Laser_Destroyer(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(red);
	hitbox.setOutlineThickness(1);

	animations.push_back(new Animation(5, 0.25, 1.2, { 0,0 }, { 1.05,0.5 }, "electroBeam5.png"));
	animations.back()->setScale({ 4,1.6 });
	animations.back()->setRotationDivation(270);
	animations.back()->PushToObject(animations.back(), this);

	Vector2f size = { animations.back()->getSize().y,animations.back()->getSize().x };
	hitbox.setSize(size * Vector2f(0.9, 1));
	hitbox.setOrigin(hitbox.getSize().x / 2, 0);	

	sprites.push_back(new SpriteOnly("laserCannon.png", Vector2f(0, 0)));
	sprites.back()->setOrigin({ 0.5,-0.25 });
	sprites.back()->setScale(0.5);
	sprites.back()->PushToObject(sprites.back(), this);

	playSpawnSound("MasterSpark.ogg");
	setTimer(0, 500);

	isBulletDestructible = false;
	Damage = 450;
	HitPoints = HitPointsMax = 10000;

	Velocity = { 0, 0 };
	Acceleration = { 0,0 };

	type = BulletType_Enemy_Laser;
}