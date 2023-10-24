#pragma once
#include "../Entiy/Bullet.h"

class BulletManager : public SceneNode
{
	public:
	BulletManager();
	~BulletManager();

	void addBullet(BulletType type,sf::Vector2f position);
	void deleteBullet(int& index);
	void updateCurrent(sf::Event& event, sf::Vector2f& MousePos) override;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override ;
	void takeTimeCurrent() override;

	int getBulletCount() { return BulletList.size(); }

	void addTarget(Entity& target);
	void removeTarget(Entity& target);

	private:
	std::vector<Bullet*> BulletList;
	std::vector<Entity*> TargetList;
};

