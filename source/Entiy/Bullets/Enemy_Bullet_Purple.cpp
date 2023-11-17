#include "../Bullet.h"

Enemy_Bullet_Purple::Enemy_Bullet_Purple(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	
	animations.push_back(new Animation(10, 10, 1, 1, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "UFO_Bullet.png"));
	animations.back()->setRotationDivation(-90);
	animations.back()->PushToObject(animations.back(), this);

	Vector2f size = { animations.back()->getSize().y,animations.back()->getSize().x };
	setHitBox(size * 0.8);

	isBulletDestructible = true;
	Damage = 60;

	playSpawnSound("(buglezap).ogg");
	Velocity = Vector2f(0, 70*SCALE );
	Acceleration = { 0,0 };

	type = BulletType_Enemy_Purple;
}