#include "../Bullet.h"

Enemy_Bullet_Egg::Enemy_Bullet_Egg(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::purple);
	
	sprites.push_back(new SpriteOnly("egg.png", Vector2f(0, 0)));
	sprites.back()->PushToObject(sprites.back(), this);
	sprites.back()->setOrigin({ 0.5, 0.5 });
	sprites.back()->setScale(0.3);

	setHitBox(sprites.back()->getSize()*0.7);

	isBulletDestructible = true;
	Damage = 50;

	Velocity = Vector2f(0, 60*SCALE );
	Acceleration = { 0,0 };

	type = BulletType_Enemy_Egg;
}