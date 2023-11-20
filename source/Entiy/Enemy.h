#pragma once
#include "Entity.h"
#include "BulletPattern.h"

enum EnemyType { EnemyType_Chicken_1, EnemyType_Boss_Chicken_1,EnemyType_UFO, EnemyType_SpaceShip, EnemyType_Henterprise };

class Enemy : public Entity
{
	public:
	Enemy(Vector2f StartPosition);

	void takeTimeCurrent() override;
	virtual void additionalBehavior() {};
	bool isFiring = false;
	int attackType = 0;
	int attackTypeMax = 0;
	bool spawnRequest = false;

	void setBulletManager(BulletManager*& EnimesBullets, BulletManager*& EnimesBullets_Vulnerable);
	void setPlayer(Player*& player) { this->player = player; };
	void setWarningZone(WarningZone*& warningZone) { this->warningZone = warningZone; };

	void resetGun();	

protected:
	short unsigned int reloadFrameID = 0;
	short unsigned int reloadFrameIDMax = 50;

	virtual void attack() {};

	EnemyType type;
	EnemyType SpawnType= EnemyType_Chicken_1;
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

class SpaceShip : public Enemy
{
	public:
	SpaceShip(Vector2f StartPosition);
	//void takeTimeCurrent() override;

	private:
		void atThreeQuarterHealth() override;
		void atHalfHealth() override;
		void atQuarterHealth() override;
		void addDeathAnimation() override;
		void attack() override;

		void additionalBehavior() override;

		void addSpaceShipBullet(bool isRotated);

		void ramming();

		int isRamming = 0;
		int RammingSpeed = 300;
};

class Henterprise : public Enemy
{
public:
	Henterprise(Vector2f StartPosition);
	//void takeTimeCurrent() override;

private:
	void atThreeQuarterHealth() override;
	void atHalfHealth() override;
	void atQuarterHealth() override;
	void addDeathAnimation() override;
	void attack() override;

	void addExplosion(int cnt);

	void additionalBehavior() override;

};






