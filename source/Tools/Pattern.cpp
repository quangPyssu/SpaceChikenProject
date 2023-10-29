#include "Pattern.h"

Pattern::~Pattern()
{
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
		tmp->setTimer( timerStart,timerEnd);

		entityListIndex.push_back(i);
	}

	switch (type)
	{
		case Circle:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
				tmp->setRootPos(CurrentPos);
				tmp->rotationDependent = true;				
				tmp->RotationDivation += i * 360 / total;
				tmp->setRotation(tmp->RotationDivation);
			}
		}
		break;

		case Square:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
				tmp->setRootPos(CurrentPos);
				tmp->rotationDependent = true;
			}
		}
		break;

		case Shower:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];

				tmp->rotationDependent = true;
				tmp->setRotation(tmp->RotationDivation);

				// each fly out from origin
				tmp->setVelocity(Vector2f((float)SCALE * this->Velocity.x , (float)SCALE * this->Velocity.y));
				tmp->setAcceleration(Vector2f((float)SCALE * this->Acceleration.x, (float)SCALE * this->Acceleration.y));
			}

			this->Velocity = { 0,0 };
			this->Acceleration = { 0,0 };
		}

		break;

		case Firework:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];

				tmp->rotationDependent = true;
				tmp->RotationDivation += i * 360 / total;
				tmp->setRotation(tmp->RotationDivation);

				// each fly out from origin
				tmp->setVelocity(Vector2f( (float)SCALE * cos(tmp->RotationDivation * pi / 180) * this->Velocity.x
					,(float)SCALE * sin(tmp->RotationDivation * pi / 180) * this->Velocity.y ));
				tmp->setAcceleration(Vector2f((float)SCALE * cos(tmp->RotationDivation * pi / 180) * this->Acceleration.x
					,(float)SCALE * sin(tmp->RotationDivation * pi / 180) * this->Acceleration.y ));
			}

			this->Velocity = { 0,0 };
			this->Acceleration = { 0,0 };
		}
		break;
		default:
		break;
	}
}

void Pattern::takeTimeCurrent()
{
	Entity::takeTimeCurrent();
	if (timerStart > 0) return;

	if (CurrentEnityState==Alive && entityList.empty())
	{
		Entity::killEntity();
		return;
	}

	for (int i = 0; i < entityList.size(); i++)
		if (entityList[i]->CurrentEnityState == EntityState::Dead)
		{
			entityList.erase(entityList.begin() + i);
			entityListIndex.erase(entityListIndex.begin() + i);
			i--;
			continue;
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
		{
			float angleRad = std::atan2(Velocity.y, Velocity.x);
			float angleDeg = angleRad * 180.0f / pi;

			if (angleDeg < 0) angleDeg += 360;
			if (angleDeg > 360) angleDeg -= 360;

			if (angleDeg > 60 && angleDeg<=180) angleDeg = 60;
			if (angleDeg < 300 && angleDeg>180) angleDeg = 300;

			setRotation(angleDeg);
		}
			break;

		case WithOwnVelocity:
		{
			for (int i = 0; i < entityList.size(); i++)
			{
				Entity* tmp = entityList[i];
				float angleRad = std::atan2(tmp->getVelocity().y, tmp->getVelocity().x);
				float angleDeg = angleRad * 180.0f / pi;
				tmp->RotationDivation=angleDeg;
			}
		}
	}
	

	for (int i = 0; i < entityList.size(); i++)
		switch (type)
		{
			case Circle:
			{
				float distance = width / 2;
				float tmp = entityList[i]->getRotation() + angleVelocity;
				tmp = min((float)360, max(tmp, (float)0));
				entityList[i]->setRotation(tmp);

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

void Pattern::setTimer(int timerStart, int timerEnd)
{
	Entity::setTimer(timerStart, timerEnd);

	for (int i = 0; i < entityList.size(); i++) entityList[i]->setTimer(timerStart, timerEnd);
}