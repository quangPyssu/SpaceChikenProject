#include "../Bullet.h"

Player_Ram_Destroyer::Player_Ram_Destroyer(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::red);
	hitbox.setOutlineThickness(1);
	hitbox.setSize(Vector2f(Constants::PlayerHitboxSize.y+20, Constants::PlayerHitboxSize.y+20));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y/2);

	animations.push_back(new Animation(30, 8, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Dreadnought_Shield.png"));
	animations.back()->PushToObject(animations.back(), this);

	/*animations.push_back(new Animation(30, 8, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Battlecruiser_Shield.png"));
	animations.back()->PushToObject(animations.back(), this);

	animations.push_back(new Animation(30, 4, 1, 1, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "BlueBurn.png"));
	animations.back()->setRotationDivation(180);
	animations.back()->setTransparency(0.4);
	animations.back()->PushToObject(animations.back(), this);*/

	playSound("MarioStar.ogg");
	setTimer(0, 650);

	isBulletDestructible = false;
	Damage = 2;

	Velocity = { 0, 0 };
	Acceleration = { 0,0 };

	type = BulletType_Player_Ram_Destroyer;
}

void Player_Ram_Destroyer::addDeathAnimation()
{
	Entity::addDeathAnimation();
}