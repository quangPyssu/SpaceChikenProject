#include "Entity.h"

Entity::Entity()
{
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Entity::updateCurrent(sf::Event& event, sf::Vector2f& MousePos)
{

}

void Entity::takeTimeCurrent()
{
	Velocity += sf::Vector2f(Acceleration.x * TIME_PER_FRAME.asSeconds(), Acceleration.y * TIME_PER_FRAME.asSeconds());
	setPosition(getPosition() + sf::Vector2f(Velocity.x * TIME_PER_FRAME.asSeconds(), Velocity.y * TIME_PER_FRAME.asSeconds()));
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	Velocity = velocity;
}

void Entity::setAcceleration(sf::Vector2f acceleration)
{
	Acceleration = acceleration;
}
