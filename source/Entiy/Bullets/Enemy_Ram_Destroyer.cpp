#include "../Bullet.h"

Enemy_Ram_Destroyer::Enemy_Ram_Destroyer(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(red);
	hitbox.setOutlineThickness(1);

	sprites.push_back(new SpriteOnly("exhaust.png", Vector2f(0, 0)));
	sprites.back()->setOrigin({ 0.5,1.2 });
	sprites.back()->setScale(0.5);
	sprites.back()->PushToObject(sprites.back(), this);

	setHitBox(sprites.back()->getSize() * Vector2f(1,0.5));

	//playSpawnSound("laserSmall.ogg");
	setTimer(0, -1);

	isBulletDestructible = false;
	Damage = 400;
	HitPoints = 1000;

	Velocity = { 0, 0 };
	Acceleration = { 0,0 };

	type = BulletType_Enemy_Ram_Destroyer;
}