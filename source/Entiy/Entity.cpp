#include "Entity.h"

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(hitbox);
}

void Entity::takeTimeCurrent()
{
	Velocity += sf::Vector2f(Acceleration.x * TIME_PER_FRAME.asSeconds(), Acceleration.y * TIME_PER_FRAME.asSeconds());
	setPosition(getPosition() + sf::Vector2f(Velocity.x * TIME_PER_FRAME.asSeconds(), Velocity.y * TIME_PER_FRAME.asSeconds()));
	hitbox.setPosition(getPosition());
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	Velocity = velocity;
}

void Entity::takeDamage(int damage)
{
	HitPoints -= damage;
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