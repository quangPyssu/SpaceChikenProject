#pragma once
#include "../Entiy/Bullet.h"
#include "../Entiy/Player.h"
#include "../Entiy/Enemy.h"
#include "BulletManager.h"
#include "../Entiy/BulletPattern.h"

enum EnemyAttackType { Attack_EggFall_1, Attack_EggBarrage, Attack_EggCircle_1  };

class EnemyManager : public SceneNode
{
public:
	EnemyManager(Player& player, BulletManager& PlayerBullets_Standard,	BulletManager& PlayerBullets_Detroyer
		,BulletManager& EnimesBullets, BulletManager& EnimesBullets_Vulnerable,WarningZone& warningZone);
	~EnemyManager();

	void takeTimeCurrent() override;

	void addEnemy(EnemyType type);
	void removeEnemy(Entity& target); 
	vector <Enemy*> enemy;

	void addBulletPattern(BulletType type, PatternType patternType, RotationType rotationType, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, bool Physics,
		int total, float width, int widthCnt, int timerStart, int timerEnd,double thisScale);

private:

	// Player, Enimes, 

	Player* player;	
	WarningZone* warningZone;

	BulletManager* PlayerBullets_Standard;
	BulletManager* PlayerBullets_Detroyer;
	BulletManager* EnimesBullets;
	BulletManager* EnimesBullets_Vulnerable;

	vector <BulletPattern*> BulletPatternList;

	vector <pair <BulletPattern*,int>> BulletPattern_Aim_For_Player;

	void fireBulletPattern();
};

