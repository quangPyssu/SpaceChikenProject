#include "Pattern.h"

Pattern::~Pattern()
{
	for (int i = 0; i < entityList.size(); i++)	entityList[i]->killEntity();
}

void Pattern::setUpPattern(PatternType type)
{
	this->type = type;
	int total = entityList.size();
	if (total == 0) return;

	switch (type)
	{
		case Circle:
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];

				tmp->setRotation(i*360/total);

				tmp->Parent = this;
				tmp->setRootPos(CurrentPos);			
			}
			
		break;
		default:
		break;
	}
}

void Pattern::takeTimeCurrent()
{
	Entity::takeTimeCurrent();

	if (entityList.empty())
	{
		CurrentEnityState = Dying;
		return;
	}

	CurrentPos = getPosition();
	angleVelocity += angleAcceleration;

	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList[i]->CurrentEnityState == EntityState::Dead)
		{
			entityList.erase(entityList.begin() + i); i--;
			continue;
		}

		switch (type)
		{
			
			case Circle:

				float distance = 150;
				float tmp= entityList[i]->getRotation()+angleVelocity;
				tmp = min( (float) 360,max(tmp,(float) 0));
				entityList[i]->setRotation(tmp);

				entityList[i]->setDivation(Vector2f(sin(tmp*pi/180)*distance, cos(tmp*pi / 180)*distance));

				break;
		}

	}
	
}






