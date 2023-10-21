#include "Enemy.h"

Enemy::Enemy(EnemyType type, Vector2f StartPosition) 
{
	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);

	switch (type)
	{
	case Enemy_Chicken_1:
		hitbox.setFillColor(Color::Blue);
		hitbox.setSize({ 20,20 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
		Velocity = { 0, 0 };
		Acceleration = { 0,0 };
		break;
	default:
		break;
	}
}