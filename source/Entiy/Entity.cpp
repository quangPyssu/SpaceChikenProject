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
	if (timerStart > 0) {
		timerStart--;
		return;
	}

	if (timerEnd != -1)
	{
		if (!timerEnd)
		{
			killEntity();
		}
		timerEnd = max(timerEnd - 1, 0);
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

			if (rotationDependent)	setRotation(Parent->getRotation() + RotationDivation);

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

void Entity::takeDamage(int damage)
{
	if (CurrentEnityState == EntityState::Alive)
	{
		if (isFlickering && isInvincibleWhenFlicker) return;

		HitPoints -= damage;

		if (!isFlickering) makeFlicker();

		if (HitPoints <= 0)
		{
			killEntity();
		}
	}
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
			killEntity();
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

sf::Vector2f Entity::getVelocity()
{
	return Velocity;
}

void Entity::takeTimeFlicker() 
{
	if (!isFlickering) return;
	Flicker::takeTimeFlicker();

	for (int i = 0; i < animations.size(); i++)	 animations[i]->setFlickerColor(flickerColor);
	
	for (int i = 0; i <sprites.size(); i++)	 sprites[i]->setFlickerColor(flickerColor);
}