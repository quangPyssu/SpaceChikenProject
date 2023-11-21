#include "../Enemy.h"

Black_Hole::Black_Hole(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);

	animations.push_back(new Animation(14, 55, 1, 1, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Black_Hole.png"));
	animations.back()->PushToObject(animations.back(), this);

	setHitBox(animations.back()->getSize() * Vector2f(0.7,0.3));

	HitPoints = HitPointsMax = 7000;

	Velocity = { 0,0 };
	Acceleration = { 0,0 };

	reloadFrameID = 290;
	reloadFrameIDMax = 290;

	attackTypeMax = 1;

	type = EnemyType_BlackHole;
	canFlicker = false;
}

void Black_Hole::attack()
{
		switch (attackTypeMax)
		{
		case 1:
			{
				BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Vortex, RotationType::defaultRotation,
										*EnimesBullets, getPosition()*(1/SCALE),
										{1,0 }, { -1,0 }, false, 5, 100, 5, *warningZone, 0, 3500, SCALE);
				tmp->setRotation(90);

				Enemy_BulletPattern_queue.push({ tmp,0 });
			}
			break;
		}
}

void Black_Hole::atHalfHealth()
{
	reloadFrameID = 250;
	reloadFrameIDMax = 250;
	//explosions
}

