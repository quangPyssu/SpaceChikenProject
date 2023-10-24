#include "Entity.h"

Entity::~Entity()
{
	for (int i = 0; i < sounds.size(); i++) delete sounds[i];
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(hitbox);
}

void Entity::takeTimeCurrent()
{
	switch (CurrentEnityState)
	{
		case EntityState::Alive:

			Acceleration += sf::Vector2f(D_Acceleration.x * TIME_PER_FRAME.asSeconds(), D_Acceleration.y * TIME_PER_FRAME.asSeconds());
			Velocity += sf::Vector2f(Acceleration.x * TIME_PER_FRAME.asSeconds(), Acceleration.y * TIME_PER_FRAME.asSeconds());
			setPosition(getPosition() + sf::Vector2f(Velocity.x * TIME_PER_FRAME.asSeconds(), Velocity.y * TIME_PER_FRAME.asSeconds()));
			hitbox.setPosition(getPosition());

			CleanDeadAssets();

			outScope();
			break;
		
		case EntityState::Dying:
			CleanDeadAssets();

			if (animations.empty() || sounds.empty()) CurrentEnityState = EntityState::Dead;

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
		HitPoints -= damage;
		if (HitPoints <= 0)
		{
			CurrentEnityState = EntityState::Dying;
			addDeathAnimation();
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
		else CurrentEnityState = EntityState::Dead;
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