#include "../Bullet.h"

Enemy_Bullet_Egg::Enemy_Bullet_Egg(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::purple);
	hitbox.setSize({ 5,20 });
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

	sprites.push_back(new SpriteOnly("egg.png", Vector2f(0, 0)));
	sprites.back()->PushToObject(sprites.back(), this);
	sprites.back()->setOrigin({ 0.5, 0.5 });
	sprites.back()->setScale(0.5);

	isBulletDestructible = true;
	Damage = 1;

	Velocity = { 0, 100 };
	Acceleration = { 0,0 };
}

void Enemy_Bullet_Egg::addDeathAnimation()
{
	Entity::addDeathAnimation();
}