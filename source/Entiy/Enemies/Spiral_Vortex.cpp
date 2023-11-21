#include "../Enemy.h"

Spiral_Vortex::Spiral_Vortex(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);

	animations.push_back(new Animation(7, 20, 3, 1, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Blue_Vortex.png"));
	animations.back()->PushToObject(animations.back(), this);

	setHitBox(animations.back()->getSize() * 0.5);

	HitPoints = HitPointsMax =3000;

	Velocity = { 0,0 };
	Acceleration = { 0,0 };

	reloadFrameID = 1000;
	reloadFrameIDMax = 1000;

	attackTypeMax = 1;

	type = EnemyType_BlackHole;
	canFlicker = false;
}

void Spiral_Vortex::attack()
{
	for (int j = 0; j < 10; j++)  // 10 egg fire around consecutively
	{
		Vector2f vel= AngleShift( velocityToB( 100*SCALE, player->getPosition()),360/10*j);
		BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Egg, PatternType::Circle, RotationType::defaultRotation, *EnimesBullets,
			getPosition(), vel, { 0,0 }, false, 1, 0, 1, *warningZone, j * 15, 2000, 1);
		tmp->setRotation(90);

		Enemy_BulletPattern_queue.push({ tmp,0 });
	}
}
