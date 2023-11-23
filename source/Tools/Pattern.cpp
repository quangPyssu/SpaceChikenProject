#include "Pattern.h"

Pattern::~Pattern()
{
	for (int i = 0; i < entityList.size(); i++) if (entityList[i]->CurrentEnityState!=Dead) 
	{
		entityList[i]->setTimer(0,0);
	}

	entityList.clear();

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
				tmp->RotationDivation += (float) i * 360 / total;
				tmp->setRotation(tmp->RotationDivation);
			}

			if (rotationType==WithOwnVelocity) rotationType = SpinOwn;
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

		case Shower: // rain down
		{
			if (width <= 0) width = 300 * SCALE;

			for (int i = 0; i < total; i++)
			{
				int x = (rand() % (int)(width * 2)) - width;
				int y = (rand() % (int)(width * 2)) - width;
				Entity* tmp = entityList[i];

				tmp->setPosition(tmp->getPosition()+Vector2f(x, y));

				tmp->rotationDependent = true;
				tmp->setRotation(tmp->RotationDivation);

				// rain down 
				tmp->setVelocity(Vector2f((float)SCALE * this->Velocity.x , (float)SCALE * this->Velocity.y));
				tmp->setAcceleration(Vector2f((float)SCALE * this->Acceleration.x, (float)SCALE * this->Acceleration.y));
			}

			this->Velocity = { 0,0 };
			this->Acceleration = { 0,0 };

			if (rotationType == WithOwnVelocity) rotationType = WithOwnVelocity;			
		}
		break;

		case Firework: // each fly out from origin
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];

				tmp->rotationDependent = true;
				tmp->RotationDivation += (float) i * 360 / total; 		
				tmp->setRotation(tmp->RotationDivation);
				
				tmp->setVelocity(Vector2f( (float)cos(tmp->RotationDivation * pi / 180) * this->Velocity.x
					,(float) sin(tmp->RotationDivation * pi / 180) * this->Velocity.y ));
				tmp->setAcceleration(Vector2f((float)cos(tmp->RotationDivation * pi / 180) * this->Acceleration.x
					,(float) sin(tmp->RotationDivation * pi / 180) * this->Acceleration.y ));
			}

			this->Velocity = { 0,0 };
			this->Acceleration = { 0,0 };
		}
		break;

		case Vortex:  // grow or skrink in size ( each spin around origin)
		{ // this->velocity determine grow or skrink
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
				tmp->setRootPos(CurrentPos);
				tmp->rotationDependent = true;
				tmp->RotationDivation += (float)i * 360 / total;
				tmp->setRotation(tmp->RotationDivation);

				tmp->setVelocity(Vector2f((float)this->Velocity.x, (float)this->Velocity.y));
				tmp->setAcceleration(Vector2f((float)this->Acceleration.x/10, (float)this->Acceleration.y/10));
			}

			if (rotationType == WithOwnVelocity) rotationType = Spin;

			this->Velocity = { 0,0 };
			this->Acceleration = { 0,0 };
		}
		break;

		case None:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];

				tmp->setPosition(getPosition());

				// each own do own thing
				tmp->setVelocity(Vector2f((float)SCALE * this->Velocity.x, (float)SCALE * this->Velocity.y));
				tmp->setAcceleration(Vector2f((float)SCALE * this->Acceleration.x, (float)SCALE * this->Acceleration.y));
			}

			this->Velocity = { 0,0 };
			this->Acceleration = { 0,0 };
			this->setPosition({ -300,-300 });
		}
		break;
		default:
		break;
	}

	switch (rotationType) //set up rotation variables
	{
		case Spin:
		{
			angleVelocity = 0.5;
			angleAcceleration = 0;
		}
		break;

		case SpinOwn:
		{
			angleVelocity = 0.5;
			angleAcceleration = 0;
		}
		break;

		case WithOwnVelocity:
		{
			angleVelocity = 0;
			angleAcceleration = 0;

			if (hasPhysics) 
				for (int i = 0; i < total; i++)
					entityList[i]->ApplyPhysics();			
		}
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

			if (angleDeg > 50 && angleDeg<=180) angleDeg = 50;
			if (angleDeg < 310 && angleDeg>180) angleDeg = 310;

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
			break;

		case WithOwnVelocityTiltUp:
		{
			for (int i = 0; i < entityList.size(); i++)
			{
				Entity* tmp = entityList[i];
				float angleRad = std::atan2(tmp->getVelocity().y, tmp->getVelocity().x);
				float angleDeg = angleRad * 180.0f / pi;

				if (angleDeg < 0) angleDeg += 360;
				if (angleDeg > 360) angleDeg -= 360;

				if (angleDeg > 50 && angleDeg <= 180) angleDeg = 50;
				if (angleDeg < 310 && angleDeg > 180) angleDeg = 310;

				tmp->RotationDivation = angleDeg;
			}
		}
			break;

		case SpinOwn:
		{
			for (int i = 0; i < entityList.size(); i++)
			{
				Entity* tmp = entityList[i];
				tmp->RotationDivation += angleVelocity;
				tmp->setRotation(tmp->RotationDivation);
			}
		}
			break;
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

			case Vortex:
			{
				width-= entityList[i]->getVelocity().x/10;
				float distance = width / 2;
				float tmp = entityList[i]->getRotation() + angleVelocity;
				tmp = min((float)360, max(tmp, (float)0));
				entityList[i]->setRotation(tmp);

				entityList[i]->setDivation(Vector2f(sin(tmp * pi / 180) * distance, cos(tmp * pi / 180) * distance));
			}
			break;
		}
}

void Pattern::setTimer(int timerStart, int timerEnd)
{
	Entity::setTimer(timerStart, timerEnd);

	for (int i = 0; i < entityList.size(); i++) entityList[i]->setTimer(timerStart+2, timerEnd);
}

void Pattern::setVelocity(Vector2f Velocity)
{
	Entity::setVelocity(Velocity);
}