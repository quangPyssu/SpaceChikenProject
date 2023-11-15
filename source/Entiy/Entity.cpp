#include "Entity.h"

Entity::~Entity()
{
	for (int i = 0; i < sounds.size(); i++) delete sounds[i];
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (timerStart > 0) return;
	target.draw(hitbox);
}

void Entity::takeTimeCurrent()
{
	if (timerEnd != -1)
	{
		timerEnd = max(timerEnd - 1, 0);

		if (!timerEnd)
		{
			killEntity();
			timerEnd = -1;
		}
	}

	switch (CurrentEnityState)
	{
		case EntityState::Alive:

			if (RootPos)
			{
				setPosition(*RootPos + Divation);
			}
			else
			{
				Velocity += sf::Vector2f(Acceleration.x * TIME_PER_FRAME.asSeconds(), Acceleration.y * TIME_PER_FRAME.asSeconds());
				setPosition(getPosition() + sf::Vector2f(Velocity.x * TIME_PER_FRAME.asSeconds(), Velocity.y * TIME_PER_FRAME.asSeconds()));
			}

			if (rotationDependent)	setRotation(baseRotation + Parent->getRotation() + RotationDivation);

			hitbox.setRotation(getRotation());

			CleanDeadAssets();

			takeTimeFlicker();

			outScope();
			break;
		
		case EntityState::Dying:
			CleanDeadAssets(); 
			if (animations.empty() && sounds.empty()) this->CurrentEnityState = EntityState::Dead;

			break;

		case EntityState::Dead:

			break;
	}
}

void Entity::CleanDeadAssets()
{
	for (int i = 0; i < animations.size(); i++)
		if (animations[i]->isAnimationFinished())
		{
			detachChild(*animations[i]);
			animations.erase(animations.begin() + i);
			i--;
		}

	for (int i = 0; i < sounds.size(); i++)
		if (sounds[i]->getStatus() == sf::Sound::Stopped)
		{
			delete sounds[i];
			sounds.erase(sounds.begin() + i);
			i--;
		}
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	Velocity = velocity;
}

Entity::damageEvent Entity::takeDamage(int damage)
{
	if (CurrentEnityState == EntityState::Alive && !timerStart)
	{
		if (isFlickering && isInvincibleWhenFlicker) return damageEvent::NoDamage;

		damageEvent tmp = Entity::damageEvent::TakeDamage;

		if (HitPoints > HitPointsMax / 2 && HitPoints - damage <= HitPointsMax / 2)
		{
			tmp = damageEvent::HalfHealth;
			atHalfHealth();
		}
		else if (HitPoints > HitPointsMax / 4 && HitPoints - damage <= HitPointsMax / 4)
		{
			tmp = damageEvent::QuarterHealth;
			atQuarterHealth();
		}

		HitPoints -= damage;

		if (!isFlickering) makeFlicker();

		if (HitPoints <= 0)
		{
			killEntity();
		}

		return tmp;
	}

	return damageEvent::NoDamage;
}

void Entity::setAcceleration(sf::Vector2f acceleration)
{
	Acceleration = acceleration;
}

bool Entity::CollitionDetection(const Entity& other)
{
	return hitbox.getGlobalBounds().intersects(other.hitbox.getGlobalBounds());
}

void Entity::ApplyPhysics()
{
	hasPhysics = true;
}

void Entity::outScope()
{
	if (getPosition().x < 0 || getPosition().x > WINDOW_SIZE.x || getPosition().y < 0 || getPosition().y > WINDOW_SIZE.y)
		if (hasPhysics)
		{
			if (getPosition().x < 0 || getPosition().x > WINDOW_SIZE.x) setVelocity({ -Velocity.x,Velocity.y });
			if (getPosition().y < 0 || getPosition().y > WINDOW_SIZE.y) setVelocity({ Velocity.x,-Velocity.y });
		}
		else if(getPosition().x < OutScopeX.ff || getPosition().x > OutScopeX.ss || getPosition().y < OutScopeY.ff || getPosition().y > OutScopeY.ss)
		{
			if (Destructible) CurrentEnityState = EntityState::Dead;
		}
}

void Entity::killEntity()
{
	if (Destructible)
	{
		CurrentEnityState = EntityState::Dying;
		addDeathAnimation();
	}
}

void Entity::addDeathAnimation()
{
	for (int i = 0; i < animations.size(); i++) detachChild(*animations[i]);
	for (int i = 0; i < sprites.size(); i++) detachChild(*sprites[i]);

	animations.clear();
	sprites.clear();
}

void Entity::playSound(string soundName)
{
	sounds.push_back(new Sound);
	sounds.back()->setBuffer(ResourceManager::getSoundBuffer(soundName));
	sounds.back()->setVolume((float) soundVolume * masterVolume / 100);
	sounds.back()->play();
}

void Entity::setTimer(int timerStart,int timerEnd)
{
	this->timerEnd = timerEnd;
	this->timerStart = timerStart;
}

void Entity::setPosition(sf::Vector2f position)
{
	sf::Transformable::setPosition(position);
	hitbox.setPosition(position);
}

void Entity::setRootPos(sf::Vector2f& rootPos)
{
	RootPos = &rootPos;
}

void Entity::setDivation(sf::Vector2f divation)
{
	Divation = divation;
}

void Entity::setHitBox(sf::Vector2f size)
{
	hitbox.setSize(size);
	hitbox.setOrigin(size.x / 2, size.y / 2);
}

sf::Vector2f Entity::getVelocity()
{
	return Velocity;
}

void Entity::setBaseRotation(float rotation)
{
	baseRotation = rotation;
}

void Entity::takeTimeFlicker() 
{
	if (!isFlickering) return;
	Flicker::takeTimeFlicker();

	for (int i = 0; i < animations.size(); i++)	 animations[i]->setFlickerColor(flickerColor);
	
	for (int i = 0; i <sprites.size(); i++)	 sprites[i]->setFlickerColor(flickerColor);
}

float Entity::angleToB(Entity* B)
{
	float angle = atan2(B->getPosition().y - getPosition().y, B->getPosition().x - getPosition().x) * 180 / pi;
	return angle;
}

float Entity::angleToB(sf::Vector2f posB)
{
	float angle = atan2(posB.y - getPosition().y, posB.x - getPosition().x) * 180 / pi;
	return angle;
}

sf::Vector2f Entity::velocityToB(double baseVelocity, Entity* B)
{
	float angle = angleToB(B);
	return sf::Vector2f(baseVelocity * cos(angle * pi / 180), baseVelocity * sin(angle * pi / 180));
}

sf::Vector2f Entity::velocityToB(double baseVelocity, sf::Vector2f posB)
{
	float angle = angleToB(posB);
	return sf::Vector2f(baseVelocity * cos(angle * pi / 180), baseVelocity * sin(angle * pi / 180));
}

sf::Vector2f Entity::AngleShift(sf::Vector2f vec, double angle)
{
	return sf::Vector2f(vec.x * cos(angle * pi / 180) - vec.y * sin(angle * pi / 180), vec.x * sin(angle * pi / 180) + vec.y * cos(angle * pi / 180));
}
