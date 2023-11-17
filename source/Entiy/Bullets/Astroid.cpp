#include "../Bullet.h"

Astroid::Astroid(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::purple);
	hitbox.setOutlineThickness(1);
	

	std::string path = "Astroid.png";

	float scale = (float)(rand() % 60 + 60) / 100;
	animations.push_back(new Animation(10, 24, 2, scale, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), path));
	animations.back()->PushToObject(animations.back(), this);

	setHitBox(animations.back()->getSize()*0.65);

	Destructible = true;
	isBulletDestructible = true;
	HitPoints = HitPointsMax = 75*scale;
	Damage = 250;

	Velocity = { 0, 100 };
	Acceleration = { 0,0 };

	type = BulletType_Astroid;
}

void Astroid::addDeathAnimation()
{
	Entity::addDeathAnimation();

	animations.push_back(new Animation(10, 8, 1, 1.2, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
	PushToObject(animations.back(), this);

	int randSound = rand() % 2;
	if (randSound == 0) playSound("rock_0.ogg"); else playSound("rock_1.ogg");
}