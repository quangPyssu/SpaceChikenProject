#include "Entity.h"

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

			outScope();
			break;
		
		case EntityState::Dying:
			for (int i = 0; i < death_animation.size(); i++)
				if (death_animation[i]->isAnimationFinished())
				{
					detachChild(*death_animation[i]);
					death_animation.erase(death_animation.begin() + i);
					i--;
				}

			if (death_animation.empty()) CurrentEnityState = EntityState::Dead;

			break;

		case EntityState::Dead:

			break;
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