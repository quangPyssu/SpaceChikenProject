#include "EnemyManager.h"

EnemyManager::EnemyManager(Player& player, BulletManager& PlayerBullets_Standard, BulletManager& PlayerBullets_Detroyer, BulletManager& EnimesBullets)
	: player(&player), PlayerBullets_Standard(&PlayerBullets_Standard), PlayerBullets_Detroyer(&PlayerBullets_Detroyer), EnimesBullets(&EnimesBullets)
{
	for (int i = 0; i < 10; i++) addEnemy(Enemy_Chicken_1);

	EnimesBullets.addTarget(player);

	//EnemyPatternList.push_back(new EnemyPattern(Chicken_Circle, *this, Vector2f(500, 500), Vector2f(-2, 0), 10, 300, 10));
	//PushToObject(EnemyPatternList.back(), this);

	//BulletPatternList.push_back(new BulletPattern(Enemy_Normal_Circle, EnimesBullets, Vector2f(500, 500), Vector2f(-2, 0),10,300,10));
	//PushToObject(BulletPatternList.back(), this);

	//BulletPatternList.push_back(new BulletPattern(Enemy_Normal_Square, EnimesBullets, Vector2f(500, 500), Vector2f(60, 50), 10, 300, 4,WithVelocity));
	//PushToObject(BulletPatternList.back(), this);

}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		detachChild(*enemy[i]);
	}
	enemy.clear();
}

void EnemyManager::addEnemy(EnemyType type)
{
	enemy.push_back(new Enemy(type, Vector2f(rand() % 1000, 100)));

	PlayerBullets_Standard->addTarget(*enemy.back());
	PlayerBullets_Detroyer->addTarget(*enemy.back());

	PushToObject(enemy.back(), this);
}

void EnemyManager::removeEnemy(Entity& target)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i] == &target)
		{
			detachChild(*enemy[i]);
			enemy.erase(enemy.begin() + i);
			return;
		}
	}
}

void EnemyManager::takeTimeCurrent()
{
	for (int i = 0; i < enemy.size(); i++)	// Enemy Fire
	{
		if (enemy[i]->CurrentEnityState == EntityState::Dead)
		{
			// Detach the child
			detachChild(*enemy[i]);

			PlayerBullets_Standard->removeTarget(*enemy[i]);
			PlayerBullets_Detroyer->removeTarget(*enemy[i]);

			// Erase it from the enemy vector
			enemy.erase(enemy.begin() + i);
			i--;
		}
		else if (enemy[i]->CurrentEnityState == EntityState::Alive && enemy[i]->isFiring)
		{
			EnimesBullets->addBullet(Enemy_Bullet_Normal, enemy[i]->getPosition());
			enemy[i]->resetGun();
		}
	}

	// Clean up the dead patterns

	for (int i = 0; i < BulletPatternList.size(); i++)
	{
		if (BulletPatternList[i]->CurrentEnityState == EntityState::Dead)
		{
			detachChild(*BulletPatternList[i]);
			BulletPatternList.erase(BulletPatternList.begin() + i);
			i--;
		}
	}

	//cout << "BulletPatternList.size() " << BulletPatternList.size() << endl;
}

