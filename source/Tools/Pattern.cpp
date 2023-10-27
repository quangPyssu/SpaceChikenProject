#include "Pattern.h"

Pattern::~Pattern()
{
	for (int i = 0; i < entityList.size(); i++)	entityList[i]->killEntity();
}

void Pattern::setUpPattern(PatternType type)
{
	hitbox.setSize(Vector2f(30,30));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
	hitbox.setFillColor(Colors::trans);

	this->type = type;
	total = entityList.size();
	if (total == 0) return;

	for (int i = 0; i < total; i++)
	{
		Entity* tmp = entityList[i];
		tmp->Parent = this;
		tmp->setRootPos(CurrentPos);
		tmp->rotationDependent = true;
		tmp->setRotation(tmp->RotationDivation);

		entityListIndex.push_back(i);
	}

	switch (type)
	{
		case Circle:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];

				tmp->RotationDivation += i * 360 / total;
			}
		}
		break;

		case Square:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
			}
		}
			break;
		default:
		break;
	}
}

void Pattern::takeTimeCurrent()
{
	Entity::takeTimeCurrent();

	if (CurrentEnityState==Alive && entityList.empty())
	{
		Entity::killEntity();
		return;
	}

	CurrentPos = getPosition();

	switch (rotationType)
	{
		case Spin:
		{
			angleVelocity += angleAcceleration;
			setRotation(getRotation() + angleVelocity);
		}
			break;

		case WithVelocity:
		{
			float angleRad = std::atan2(Velocity.y, Velocity.x);
			float angleDeg = angleRad * 180.0f / pi;
			setRotation(angleDeg);
		}
			break;

		case tiltUp:
			break;
	}
	

	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList[i]->CurrentEnityState == EntityState::Dead)
		{
			entityList.erase(entityList.begin() + i); 
			entityListIndex.erase(entityListIndex.begin() + i);
			i--;
			continue;
		}

		switch (type)
		{
			case Circle:
			{
				float distance = width / 2;
				float tmp = entityList[i]->getRotation() + angleVelocity;
				tmp = min((float)360, max(tmp, (float)0));
				//entityList[i]->setRotation(tmp);

				entityList[i]->setDivation(Vector2f(sin(tmp * pi / 180) * distance, cos(tmp * pi / 180) * distance));
			}
				break;

			case Square:
			{
				int tmpWidth = width / (widthCnt - 1);

				entityList[i]->setDivation(Vector2f((entityListIndex[i] % widthCnt) * tmpWidth, (entityListIndex[i] / widthCnt) * tmpWidth));
			}
				break;
		}

	}
	
}






