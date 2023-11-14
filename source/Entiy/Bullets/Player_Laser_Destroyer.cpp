#include "../Bullet.h"

Player_Laser_Destroyer::Player_Laser_Destroyer(Vector2f StartPosition) : Bullet(StartPosition)
{
	setDivation({0,-50});
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::red);
	hitbox.setOutlineThickness(1);
	hitbox.setSize(Vector2f(150, (double)SCALE * 1000));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y);

	animations.push_back(new Animation(15, 7, 1, 0.75, { 0,0 }, { 1,0.5 }, Vector2f(0, 0), "BigBeam.png"));
	animations.back()->setRotationDivation(90);
	animations.back()->setResetFrame(5);
	animations.back()->PushToObject(animations.back(), this);

	animations.push_back(new Animation(15, 7, 1, 1, { 0,0 }, { -0.18,0.5 }, Vector2f(0, 0), "BigBeamBody.png"));
	animations.back()->setScale({ 50,1.35 });
	animations.back()->setRotationDivation(270);
	animations.back()->setResetFrame(5);
	animations.back()->PushToObject(animations.back(), this);
	animations.back()->setTransparency(1);
		
	playSound("MasterSpark.ogg"); 
	setTimer(10, 380);

	isBulletDestructible = false;
	Damage = 1;

	Velocity = { 0, 0 };
	Acceleration = { 0,0 };

	type = BulletType_Player_Laser_Destroyer;
}

void Player_Laser_Destroyer::addDeathAnimation()
{
	Entity::addDeathAnimation();
}