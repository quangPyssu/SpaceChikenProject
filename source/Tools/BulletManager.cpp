#include "BulletManager.h"

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{
	BulletList.clear();
}

void BulletManager::addBullet(BulletType type, sf::Vector2f position)
{
	unique_ptr <Bullet> tmp2 = std::make_unique<Bullet>(type,position);

	BulletList.push_back(std::move(tmp2));
}

void BulletManager::updateCurrent(sf::Event& event, sf::Vector2f& MousePos)
{

}

void BulletManager::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < BulletList.size(); i++)
	{
		target.draw(*BulletList[i], states);
	}
}

void BulletManager::deleteBullet(int& index)
{
	BulletList.erase(BulletList.begin() + index);
	index--;
}

void BulletManager::takeTimeCurrent()
{
	for (int i = 0; i < BulletList.size(); i++)
	{
		BulletList[i]->takeTimeCurrent();
		if (BulletList[i]->isDead)
		{
			deleteBullet(i);
			continue;
		}

		for (int j=0;j < TargetList.size();j++)
		{
			if (BulletList[i]->CollitionDetection(*TargetList[j]))
			{
				TargetList[j]->takeDamage(BulletList[i]->Damage);

				if (BulletList[i]->Destructible)
				{
					deleteBullet(i);
					break;
				}
			}
		}
	}


};





