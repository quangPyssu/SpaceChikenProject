#include "../Bullet.h"

Player_Bullet_Normal::Player_Bullet_Normal(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::red);
	hitbox.setOutlineThickness(1);

	animations.push_back(new Animation(10, 11, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Bullet.png"));
	animations.back()->setRotationDivation(-90);
	animations.back()->PushToObject(animations.back(), this);

	Vector2f size = { animations.back()->getSize().y,animations.back()->getSize().x };
	setHitBox(size*0.8);

	playSpawnSound("(laser).ogg");

	isBulletDestructible = true;
	Damage = 20;

	Velocity = Vector2f( 0, -300 * SCALE);
	Acceleration = Vector2f( 0,SCALE*(- 15));

	type = BulletType_Player_Normal;
}