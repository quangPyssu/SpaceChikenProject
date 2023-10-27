#pragma once
#include "../Entiy/Bullet.h"
#include "../Entiy/Player.h"
#include "../Entiy/Enemy.h"
#include "BulletManager.h"
#include "../Entiy/BulletPattern.h"
//#include "../Entiy/EnemyPattern.h"
//#include "../Tools/Pattern.h"

class EnemyManager : public SceneNode
{
public:
	EnemyManager(Player& player, BulletManager& PlayerBullets_Standard,	BulletManager& PlayerBullets_Detroyer,BulletManager& EnimesBullets);
	~EnemyManager();

	void takeTimeCurrent() override;

	void addEnemy(EnemyType type);
	void removeEnemy(Entity& target); 
	vector <Enemy*> enemy;

private:

	// Player, Enimes, 

	Player* player;	

	BulletManager* PlayerBullets_Standard;
	BulletManager* PlayerBullets_Detroyer;
	BulletManager* EnimesBullets;

	vector <BulletPattern*> BulletPatternList;
	//vector <EnemyPattern*> EnemyPatternList;
};

