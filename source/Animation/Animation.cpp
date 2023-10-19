#include "Animation.h"

Animation::Animation(unsigned short animationSpeed, unsigned short frameWidth, unsigned short floorCnt, double Scale, Vector2f Position, Vector2f Origin, const std::string& i_texture_location)
{
	this->animationSpeed = animationSpeed;
	this->frameWidth = frameWidth;
	this->floorCnt = floorCnt;
	if (!floorCnt) this->floorCnt = 1;

	texture = ResourceManager::getTexture(i_texture_location);	

	totalFrames = (texture.getSize().x / frameWidth)*floorCnt;
	FramePerFloor = totalFrames / floorCnt;

	floorHeight = texture.getSize().y / floorCnt;
	
	sprite.setTexture(texture);

	sprite.setScale(Scale*SCALE, Scale*SCALE);
	sprite.setPosition(Position);

	sprite.setOrigin(Vector2f(Origin.x*frameWidth,Origin.y*floorHeight));
}

void Animation::takeTimeCurrent() 
{
	animationFrameID++;
	//cout << "Animation::updateCurrent " << animationFrameID << endl << " " << currentFrame << endl;

	while (animationFrameID >= animationSpeed)
	{
		animationFrameID -= animationSpeed;
		currentFrame++;

		if (currentFrame == totalFrames)
		{
			currentFrame = 0;
		}
	}

	currentFloor = currentFrame / FramePerFloor;

	sprite.setTextureRect(sf::IntRect(currentFrame% FramePerFloor * frameWidth, floorHeight*currentFloor, frameWidth, floorHeight));
}

void Animation::updateCurrent(Event& event, Vector2f& MousePos)
{
}

void Animation::setPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

void Animation::setOrigin(Vector2f origin)
{
	sprite.setPosition(origin);
}

void Animation::setRotation(float rotation)
{
	sprite.setRotation(rotation);
}

void Animation::setScale(Vector2f scale)
{
	sprite.setScale(scale);
}

void Animation::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(sprite);
}

void Animation::reset()
{
	animationFrameID = 0;
	currentFrame = 0;
}