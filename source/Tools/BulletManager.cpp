#include "BulletManager.h"

BulletManager::BulletManager(Player& player) : player(&player)
{

}

BulletManager::~BulletManager()
{
	BulletList.clear();
}

void BulletManager::addBullet(BulletType type,sf::Vector2f position)
{
	Bullet* tmp = new Bullet(type, position);

	switch (type)
	{	
	case Player_Bullet_Normal:
		break;
	case Enemy_Bullet_Normal:
		break;
	case Player_Bullet_Destroyer:
		break;
	case Player_Laser_Destroyer:
		tmp->setRootPos(player->PlayerCurPos);//remember to split this into two
		break;
	default:
		break;
	}

	BulletList.push_back(tmp);
	BulletList.back()->PushToObject(BulletList.back(), this);
}

void BulletManager::addTarget(Entity& target)
{
	TargetList.push_back(&target);
}

void BulletManager::addTarget(BulletManager& target)
{
	BulletManagerList.push_back(&target);
}

void BulletManager::removeTarget(Entity& target)
{
	// Search for the target in the list of targets and remove it
	TargetList.erase(std::remove(TargetList.begin(), TargetList.end(), &target), TargetList.end());
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
		if (BulletList[i]->CurrentEnityState == EntityState::Dead)
		{
			deleteBullet(i);
			continue;
		}

		if (BulletList[i]->timerStart) continue;

		if (BulletList[i]->CurrentEnityState == EntityState::Alive)
			for (int j = 0; j < TargetList.size(); j++)
				if (TargetList[j]->CurrentEnityState == EntityState::Alive)
				{
					if (BulletList[i]->CollitionDetection(*TargetList[j]))
					{
						TargetList[j]->takeDamage(BulletList[i]->Damage);

						if (BulletList[i]->isBulletDestructible)
						{
							BulletList[i]->killEntity();
							break;
						}
					}
				}
				else if (TargetList[j]->CurrentEnityState == EntityState::Dead)
				{
					TargetList.erase(TargetList.begin() + j);
					j--;
				}


		if (BulletList[i]->CurrentEnityState == EntityState::Alive)
			for (int j = 0; j < BulletManagerList.size(); j++)
			{
				for (int k = 0; k < BulletManagerList[j]->BulletList.size(); k++) if (BulletManagerList[j]->BulletList[k]->CurrentEnityState == EntityState::Alive)
				{
					if (BulletList[i]->CollitionDetection(*BulletManagerList[j]->BulletList[k]))
					{
						BulletManagerList[j]->BulletList[k]->takeDamage(BulletList[i]->Damage);

						if (BulletList[i]->isBulletDestructible)
						{
							BulletList[i]->killEntity();
							break;
						}
					}
				}
			}
		
	}

	

};