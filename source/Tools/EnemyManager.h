#pragma once
#include "../Entiy/Bullet.h"
#include "../Entiy/Player.h"
#include "../Entiy/Enemy.h"
#include "BulletManager.h"
#include "../Entiy/BulletPattern.h"

enum EnemyAttackType { Attack_Chicken_1, };

class EnemyManager : public SceneNode
{
public:
	EnemyManager(Player& player, BulletManager& PlayerBullets_Standard,	BulletManager& PlayerBullets_Detroyer
		,BulletManager& EnimesBullets, BulletManager& EnimesBullets_Vulnerable, BulletManager& EnimesBullets_Indestructible);
	~EnemyManager();

	void takeTimeCurrent() override;

	void addEnemy(EnemyType type);
	void removeEnemy(Entity& target); 
	vector <Enemy*> enemy;

	std::queue <EnemyAttackType> AttackQueueType;
	std::queue <Vector2f> AttackQueuePosition;

private:

	// Player, Enimes, 

	Player* player;	

	BulletManager* PlayerBullets_Standard;
	BulletManager* PlayerBullets_Detroyer;
	BulletManager* EnimesBullets;
	BulletManager* EnimesBullets_Vulnerable;
	BulletManager* EnimesBullets_Indestructible;
};

