#pragma once
#include "Entity.h"
#include "BulletPattern.h"

enum EnemyType { EnemyType_Chicken_1, EnemyType_Boss_Chicken_1,EnemyType_UFO, EnemyType_SpaceShip, EnemyType_Henterprise, 
	EnemyType_BlackHole, EnemyType_SemiVortex, EnemyType_SprialVortex,EnemyType_Boss_Chicken_2
};

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
	Vector2f spawnVelocity = { 0,0 };

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

private:

	void addDeathAnimation() override;
	void attack() override;
};

class UFO : public Enemy
{	
	public:
	UFO(Vector2f StartPosition);

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

private:
	void atThreeQuarterHealth() override;
	void atHalfHealth() override;
	void atQuarterHealth() override;
	void addDeathAnimation() override;
	void attack() override;

	void addExplosion(int cnt);

	void additionalBehavior() override;

};

class Black_Hole : public Enemy
{
public:
	Black_Hole(Vector2f StartPosition);

private:
	void attack() override;

	void atHalfHealth() override;
};

class Semi_Vortex : public Enemy
{
public:
	Semi_Vortex(Vector2f StartPosition);

private:
	void attack() override;
};

class Spiral_Vortex : public Enemy
{
public:
	Spiral_Vortex(Vector2f StartPosition);

private:
	void attack() override;
};


class Boss_Chicken_2 : public Enemy
{
public:
	Boss_Chicken_2(Vector2f StartPosition);

private:
	void atThreeQuarterHealth() override;
	void atHalfHealth() override;
	void atQuarterHealth() override;
	void addDeathAnimation() override;
	void attack() override;

	void FireworkAttack();
};





