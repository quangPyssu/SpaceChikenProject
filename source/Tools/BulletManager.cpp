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
	Bullet* tmp = new Bullet(type,position);

	BulletList.push_back(tmp);
	BulletList.back()->PushToObject(BulletList.back(),this);
}

void BulletManager::addTarget(Entity& target)
{
	TargetList.push_back(&target);
}

void BulletManager::updateCurrent(sf::Event& event, sf::Vector2f& MousePos)
{

}

void BulletManager::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	/*for (int i = 0; i < BulletList.size(); i++)
	{
		BulletList[i]->draw(target, states);
	}*/
}

void BulletManager::deleteBullet(int& index)
{
	detachChild(*BulletList[index]);
	BulletList.erase(BulletList.begin() + index);
	index--;
}

void BulletManager::takeTimeCurrent()
{
	for (int i = 0; i < BulletList.size(); i++)
	{
		if (BulletList[i]->isDead)
		{
			deleteBullet(i);
			continue;
		}

		//BulletList[i]->takeTimeCurrent();

		for (int j=0;j < TargetList.size();j++)
		{
			if (BulletList[i]->CollitionDetection(*TargetList[j]))
			{
				TargetList[j]->takeDamage(BulletList[i]->Damage);				

				if (TargetList[j]->isDead)
				{
					TargetList.erase(TargetList.begin() + j);
					j--;
				}

				if (BulletList[i]->Destructible)
				{
					deleteBullet(i);
					break;
				}
			}
		}
	}


};





