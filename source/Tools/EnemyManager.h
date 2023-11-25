#pragma once
#include "../Entiy/Bullet.h"
#include "../Entiy/Player.h"
#include "../Entiy/Enemy.h"
#include "../Tools/SubTitle.h"
#include "BulletManager.h"
#include "../Entiy/BulletPattern.h"

enum EnemyAttackType { Attack_EggFall_1, Attack_EggBarrage, Attack_EggCircle_1  };

class BulletPattern;

class EnemyManager : public SceneNode
{
public:
	EnemyManager(Player& player, BulletManager& PlayerBullets_Standard,	BulletManager& PlayerBullets_Detroyer);
	~EnemyManager();

	void takeTimeCurrent() override;

	void addEnemy(EnemyType type);
	void addEnemy(EnemyType type,Vector2f Position,Vector2f Velocity,Vector2f Acceleration,int timerEnd);
	vector <Enemy*> enemy;

	void addBulletPattern(BulletType type, PatternType patternType, RotationType rotationType, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, bool Physics,
		int total, float width, int widthCnt, int timerStart, int timerEnd,double thisScale);

	void addBulletPattern(BulletPattern* bulletPattern);

private:

	// Player, Enimes, 

	Player* player;	
	WarningZone* warningZone;

	BulletManager* PlayerBullets_Standard;
	BulletManager* PlayerBullets_Detroyer;
	BulletManager* EnimesBullets;
	BulletManager* EnimesBullets_Vulnerable;

	vector <BulletPattern*> BulletPatternList;

	vector <pair <BulletPattern*,int>> BulletPattern_Aim_For_Player; //

	// the one that last update 
	SubTitle* dummy=null;
	

	void fireBulletPattern();

	friend class Enemy;
	friend class Boss_Chicken_1;
};

