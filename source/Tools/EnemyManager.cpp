#include "EnemyManager.h"

EnemyManager::EnemyManager(Player& player, BulletManager& PlayerBullets_Standard, BulletManager& PlayerBullets_Detroyer
	, BulletManager& EnimesBullets, BulletManager& EnimesBullets_Vulnerable, BulletManager& EnimesBullets_Indestructible)
	: player(&player), PlayerBullets_Standard(&PlayerBullets_Standard), PlayerBullets_Detroyer(&PlayerBullets_Detroyer)
	, EnimesBullets(&EnimesBullets) , EnimesBullets_Vulnerable(&EnimesBullets_Vulnerable), EnimesBullets_Indestructible(&EnimesBullets_Indestructible)
{

	EnimesBullets.addTarget(player);
	EnimesBullets_Vulnerable.addTarget(player);
	EnimesBullets_Indestructible.addTarget(player);
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemy.size(); i++) if (enemy[i] != nullptr) 
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
			switch (enemy[i]->type)
			{
				case Enemy_Chicken_1:
				{
					AttackQueuePosition.push(enemy[i]->getPosition());
					AttackQueueType.push(EnemyAttackType::Attack_Chicken_1);
				}
				break;
			}

			enemy[i]->resetGun();
		}
	}	

	//cout << "BulletPatternList.size() " << BulletPatternList.size() << endl;
}

