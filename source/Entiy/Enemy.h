#pragma once
#include "Entity.h"
#include "BulletPattern.h"

enum EnemyType { EnemyType_Chicken_1, EnemyType_Boss_Chicken_1,EnemyType_UFO };

class Enemy : public Entity
{
	public:
	Enemy(Vector2f StartPosition);

	void takeTimeCurrent() override;
	bool isFiring = false;
	int attackType = 0;
	int attackTypeMax = 0;

	void setBulletManager(BulletManager*& EnimesBullets, BulletManager*& EnimesBullets_Vulnerable);
	void setPlayer(Player*& player) { this->player = player; };
	void setWarningZone(WarningZone*& warningZone) { this->warningZone = warningZone; };

	void resetGun();	

protected:
	short unsigned int reloadFrameID = 0;
	short unsigned int reloadFrameIDMax = 50;

	virtual void attack() {};

	EnemyType type;
	friend class EnemyManager;
	
	BulletManager* EnimesBullets=NULL;
	BulletManager* EnimesBullets_Vulnerable=NULL;		
	Player* player=NULL;	
	WarningZone* warningZone=NULL;

	queue <pair <BulletPattern*, int>> Enemy_BulletPattern_queue; //
};

class EnemyFactory
{
	public:
		static Enemy* createEnemy(EnemyType type, Vector2f StartPosition);
};

class Boss_Chicken_1 : public Enemy
{
public:
	Boss_Chicken_1(Vector2f StartPosition);	
	//void takeTimeCurrent() override;

private:

	void atHalfHealth() override;
	void atQuarterHealth() override;
	void addDeathAnimation() override;
	void attack() override;
};

class Enemy_Chicken_1 : public Enemy
{
public:
	Enemy_Chicken_1(Vector2f StartPosition);
	//void takeTimeCurrent() override;

private:

	void addDeathAnimation() override;
	void attack() override;
};

class UFO : public Enemy
{	
	public:
	UFO(Vector2f StartPosition);
	//void takeTimeCurrent() override;

private:
	void atHalfHealth() override;
	void atQuarterHealth() override;
	void addDeathAnimation() override;
	void attack() override;

};






