#include "Animation.h"

Animation::Animation(unsigned short animationSpeed, unsigned short widthCnt, unsigned short floorCnt, double Scale, Vector2f Position, Vector2f Origin, const std::string& i_texture_location)
{
	texture = ResourceManager::getTexture(i_texture_location);

	this->animationSpeed = animationSpeed;
	this->floorCnt = floorCnt;

	Width = texture.getSize().x/widthCnt;
	Height = texture.getSize().y / floorCnt;
	
	if (!floorCnt) this->floorCnt = 1;	

	totalFrames = widthCnt*floorCnt;
	FramePerFloor = totalFrames / floorCnt;
	
	sprite.setTexture(texture);

	sprite.setScale(Scale*SCALE, Scale*SCALE);
	sprite.setPosition(Position);

	sprite.setOrigin(Vector2f(Origin.x*Width,Origin.y*Height));

	isRootSet = true;
}

Animation::Animation(unsigned short animationSpeed, unsigned short widthCnt, unsigned short floorCnt, double Scale, Vector2f Position, Vector2f Origin, Vector2f divation, const std::string& i_texture_location)
	: Animation(animationSpeed, widthCnt, floorCnt, Scale, Position, Origin, i_texture_location)
{
	this->divation = divation;
	isRootSet = false;
}

Animation::Animation(unsigned short animationSpeed, unsigned short widthCnt, unsigned short floorCnt, double Scale, Vector2f Position, Vector2f Origin, Vector2f divation, const std::string& i_texture_location, int TotalTime)
	: Animation(animationSpeed, widthCnt, floorCnt, Scale, Position, Origin, divation, i_texture_location)
{
	this->totalTime = TotalTime;
	hasLimitedTime = true;
}

void Animation::takeTimeCurrent() 
{
	if (hasLimitedTime)
	{
		totalTime = max(totalTime - 1, 0);
		if (totalTime == 0) return;
	}

	animationFrameID++;
	//cout << "Animation::updateCurrent " << animationFrameID << endl << " " << currentFrame << endl;

	while (animationFrameID >= animationSpeed)
	{
		animationFrameID -= animationSpeed;
		currentFrame+=pingPongDirection;

		if (isPingPong)
		{
			if (currentFrame == totalFrames) currentFrame--,pingPongDirection = -1;
			else if (currentFrame == 0) pingPongDirection = 1;
		}
		else
		if (currentFrame == totalFrames) currentFrame = resetFrame;
	}

	currentFloor = currentFrame / FramePerFloor;

	sprite.setTextureRect(sf::IntRect(currentFrame%FramePerFloor * Width, Height*currentFloor, Width, Height));

	if (!isRootSet)
	{
		setPosition(this->Parent->getPosition() + divation);
	}

	setRotation(this->Parent->getRotation() + rotationDivation);
	sprite.setRotation(getRotation());
}

bool Animation::isAnimationFinished()
{
	return hasLimitedTime && totalTime<=0;
}

void Animation::setPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

void Animation::setOrigin(Vector2f origin)
{
	sprite.setPosition(origin);
}

void Animation::setRotationDivation(float rotationDivation)
{
	this->rotationDivation = rotationDivation;
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

void Animation::makePingPong()
{
	isPingPong = true;
}

void Animation::setDivation(Vector2f divation)
{
	this->divation = divation;
}

void Animation::setResetFrame(int resetFrame)
{
	this->resetFrame = resetFrame;
}