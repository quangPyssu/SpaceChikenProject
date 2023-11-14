#include "Flicker.h"

void Flicker::makeFlicker()
{
	if (isFlickering || !canFlicker) return;

	currentTime = totalTime;
	isFlickering = true;
}

void Flicker::makeSuperFlicker(int flickerTime)
{
	currentTime = flickerTime;
	isFlickering = true;
}

void Flicker::takeTimeFlicker()
{
	if (!isFlickering) return;

	currentTime = std::max(0, currentTime - 1);
	
	if (!currentTime) reset();

	flickerFrameID++;

	while (flickerFrameID >= flickerSpeed)
	{
		flickerFrameID -= flickerSpeed;
		currentFrame += 1;

		if (currentFrame == totalFrames) currentFrame = 0;		
	}

	flickerColor = sf::Color(255, 255, 255, 255 - baseAlpha*currentFrame);
}

void Flicker::reset()
{
	flickerFrameID = 0;
	currentFrame = 0;
	currentTime = totalTime;

	isFlickering = false;

	flickerColor = sf::Color(255, 255, 255, 255);
}