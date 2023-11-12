#include "../Bullet.h"

Astroid::Astroid(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::purple);
	hitbox.setOutlineThickness(1);
	hitbox.setSize({ 72,72 });
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

	int astroidId = rand() % 3;
	std::string path = "Astroid_" + std::to_string(astroidId) + ".png";
	sprites.push_back(new SpriteOnly(path, Vector2f(0, 0)));
	sprites.back()->PushToObject(sprites.back(), this);
	sprites.back()->setOrigin({ 0.5, 0.5 });
	sprites.back()->setScale(1);

	animations.push_back(new Animation(10, 4, 1, 1.2, WINDOW_SIZE, { 0.5,0.6 }, Vector2f(0, 0), "BlueBurn.png"));
	animations.back()->rotationDependent = 0;
	animations.back()->setTransparency(0.4);
	animations.back()->setRotationDivation(270);
	PushToObject(animations.back(), this);

	Destructible = true;
	isBulletDestructible = true;
	HitPoints = HitPointsMax = 75;
	Damage = 5;

	Velocity = { 100, 100 };
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