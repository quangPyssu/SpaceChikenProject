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

	setScale(Vector2f( Scale,Scale ));
	if (Position != Vector2f(0, 0)) setPosition(Position);
	else setPosition(Vector2f(-300,-300));

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

Animation::Animation(unsigned short animationSpeed, float FrameWidth, double Scale, Vector2f Position, Vector2f Origin, const std::string& i_texture_location)
{
	texture = ResourceManager::getTexture(i_texture_location);

	this->animationSpeed = animationSpeed;	

	totalWidth = texture.getSize().x;
	Width = totalWidth*FrameWidth;
	Height = texture.getSize().y;

	totalFrames = 0;
	FramePerFloor = 0;

	sprite.setTexture(texture);

	setScale(Vector2f(Scale, Scale));

	if (Position != Vector2f(0, 0)) setPosition(Position);
	else setPosition(Vector2f(-300, -300));

	sprite.setOrigin(Vector2f(Origin.x*Width, Origin.y*Height));

	isRootSet = false;

	this->floorCnt = 1;
}


void Animation::takeTimeCurrent() 
{
	if (hasLimitedTime)
	{
		totalTime = max(totalTime - 1, 0);
		if (totalTime == 0) return;
	}

		animationFrameID++;

	//if totalFrames==0 then move sprite instead of frame change

		if (totalFrames)
		{
			while (animationFrameID >= animationSpeed)
			{
				animationFrameID -= animationSpeed;
				currentFrame += pingPongDirection;

				if (isPingPong)
				{
					if (currentFrame == totalFrames) currentFrame--, pingPongDirection = -1;
					else if (currentFrame == 0) pingPongDirection = 1;
				}
				else if (currentFrame == totalFrames) currentFrame = resetFrame;
			}


			currentFloor = currentFrame / FramePerFloor;

			sprite.setTextureRect(sf::IntRect(currentFrame % FramePerFloor * Width, Height * currentFloor, Width, Height));
		}
		else
		{
			animationFrameID = 0;
			totalWidth -= animationSpeed;
			if (totalWidth <= Width ) totalWidth = texture.getSize().x;

			sprite.setTextureRect(sf::IntRect(texture.getSize().x - totalWidth, 0, Width, Height));
		}

	if (!isRootSet)	setPosition(this->Parent->getPosition() + divation);

	if (RotationDependent)
	{
		setRotation(this->Parent->getRotation() + rotationDivation);
		sprite.setRotation(getRotation());
	}
}

bool Animation::isAnimationFinished()
{
	return hasLimitedTime && totalTime<=0;
}

void Animation::setPosition(Vector2f pos)
{
	Transformable::setPosition(pos);
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
	sprite.setScale(scale*Vector2f(SCALE,SCALE));
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

void Animation::setFlickerColor(sf::Color color)
{
	sprite.setColor(color);
}

void Animation::setTransparency(float transparency)
{
	sprite.setColor(sf::Color(255, 255, 255, transparency*255));
}

void Animation::setCurrentFrame(int currentFrame)
{
	this->currentFrame = currentFrame;
}

Vector2f Animation::getSize()
{
	return Vector2f(Width, Height)*sprite.getScale();
}