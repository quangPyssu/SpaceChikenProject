#include "../Enemy.h"

Henterprise::Henterprise(Vector2f StartPosition) : Enemy(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Color::Blue);
	hitbox.setOutlineThickness(1);

	sprites.push_back(new SpriteOnly("henterprise.png", Vector2f(0, 0)));
	sprites.back()->setScale(0.5);
	sprites.back()->setOrigin({ 0.5,0.5 });
	sprites.back()->PushToObject(sprites.back(), this);

	hitbox.setSize(sprites.back()->getSize() * Vector2f(0.95,0.4));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y*1.7);
	canFlicker = false;
	spawnVelocity = { 50,0 };

	HitPoints = HitPointsMax = 5000;
	
	Velocity = { 0,0 };
	Acceleration = { 0,0 };

	reloadFrameID = 40;
	reloadFrameIDMax = 450;

	attackTypeMax = 1;

	type = EnemyType_Henterprise;
	SpawnType = EnemyType_UFO;	
}

void Henterprise::addDeathAnimation()
{
	Entity::addDeathAnimation();
	addExplosion(15);

	playSound("PlayerExplode.ogg");	
}

void Henterprise::attack()
{
	
	for (int i = 0; i < 4; i++)
				{
					BulletPattern* tmp = new BulletPattern(BulletType::BulletType_Enemy_Laser, PatternType::Square, RotationType::defaultRotation, 
						*EnimesBullets,getPosition()-Vector2f(hitbox.getSize().x*(0.05*i+0.175), -hitbox.getSize().y*0.2*(4-i)),
						{0,0}, {0,0}, false, 1, 2000, 1, *warningZone, i * 100, 30, 1);
					tmp->setRotation(90);

					Enemy_BulletPattern_queue.push({ tmp,0 });

					BulletPattern* tmpp = new BulletPattern(BulletType::BulletType_Enemy_Laser, PatternType::Square, RotationType::defaultRotation,
						*EnimesBullets, getPosition() + Vector2f(hitbox.getSize().x * (0.05 * i + 0.175), hitbox.getSize().y * 0.2 * (4 - i)),
						{ 0,0 }, { 0,0 }, false, 1, 2000, 1, *warningZone, i * 100+10, 30, 1);
					tmpp->setRotation(90);

					Enemy_BulletPattern_queue.push({ tmpp,0 });
				}
			
}

void Henterprise::atThreeQuarterHealth()
{	
	addExplosion(5);
	
	EnimesBullets->addBullet(BulletType_Enemy_Laser_Destroyer, getPosition());
}

void Henterprise::atHalfHealth()
{
	//explosions
	addExplosion(10);

	playSound("PlayerExplode.ogg");
	EnimesBullets->addBullet(BulletType_Enemy_Laser_Destroyer, getPosition());
	spawnRequest = true;	
}

void Henterprise::atQuarterHealth()
{
	addExplosion(10);

	playSound("PlayerExplode.ogg");
	EnimesBullets->addBullet(BulletType_Enemy_Laser_Destroyer, getPosition());
	SpawnType = EnemyType_Boss_Chicken_1;
	spawnRequest = true;
}

void Henterprise::additionalBehavior()
{
	if (!isGoingToPos) gotoPosition(Vector2f(400, 80) * SCALE,50);
}

void Henterprise::addExplosion(int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		int tolTimer = rand() % 600;
		Vector2f Pos = Vector2f(rand() % 300*(i&1 ? -1 : 1), rand() % 100);
		animations.push_back(new Animation(randInt(12)+8, 8, 1, 2, WINDOW_SIZE, Vector2f(0.5, 0.5), Pos, "Explosion.png", tolTimer));
		PushToObject(animations.back(), this);
	}
}