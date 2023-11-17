#include "../Bullet.h"

Player_Bullet_Minigun::Player_Bullet_Minigun(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::red);
	hitbox.setOutlineThickness(1);
	float angleDivation = (float) randInt(11)-5;

	sprites.push_back(new SpriteOnly("microgun-bullet.png", Vector2f(0, 0)));
	sprites.back()->setRotationDivation(-90);
	sprites.back()->setOrigin(Vector2f(0.5, 0.5));
	sprites.back()->setScale(0.1);
	sprites.back()->PushToObject(sprites.back(), this);

	Vector2f size = { sprites.back()->getSize().y,sprites.back()->getSize().x };
	setHitBox(size*0.8);	

	playSpawnSound("(defaultweapon).ogg");	

	isBulletDestructible = true;
	Damage = 10;

	Velocity = AngleShift(Vector2f( 0, -375*SCALE),angleDivation);
	setRotation(angleDivation);
	Acceleration = { 0,0 };

	type = BulletType_Player_Minigun;
}