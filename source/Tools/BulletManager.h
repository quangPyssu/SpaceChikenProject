#pragma once
#include "../Entiy/Bullet.h"
#include "../Entiy/Player.h"

class BulletManager : public SceneNode
{
	public:
	BulletManager(Player& player);
	~BulletManager();

	void addBullet(BulletType type, sf::Vector2f position);
	void deleteBullet(int& index);
	void takeTimeCurrent() override;

	int getBulletCount() { return BulletList.size(); }

	void addTarget(Entity& target);
	void addTarget(BulletManager& target);
	void removeTarget(Entity& target);

	
private:
	std::vector<Bullet*> BulletList;
	std::vector<Entity*> TargetList;
	std::vector<BulletManager*> BulletManagerList;

	Player* player=null;	

	friend class GameState;
	friend class BulletPattern;
};

