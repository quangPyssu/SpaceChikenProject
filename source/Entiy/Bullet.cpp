#include "Bullet.h"

Bullet::Bullet(BulletType type,Vector2f StartPosition) : type(type)
{
	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);

	switch (type)
	{
	case Constants::Normal:
			hitbox.setFillColor(Color::Red);
			hitbox.setSize({ 5,20 });
			hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
			Velocity = { 0, -100 };
			Acceleration = {0,-30};
		break;
	default:
		break;
	}
}

void Bullet::takeTimeCurrent()
{
	Entity::takeTimeCurrent();

	//outscope
	if (getPosition().x < 0 || getPosition().x > WINDOW_SIZE.x || getPosition().y < 0 || getPosition().y > WINDOW_SIZE.y)
	{
		isDead = true;
	}
}





