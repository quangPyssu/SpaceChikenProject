#include "SFML/Graphics.hpp"

#pragma once

class Flicker 
{
private:
	unsigned short flickerFrameID=0;
	//The higher the value, the slower the flicker.
	unsigned short currentFrame=0;
	//We can find this by dividing the width of the image by the frame width.
	unsigned short totalFrames=3;

	//The total time of the flicker.
	unsigned short currentTime = 0;

public:
	unsigned short flickerSpeed = 10;
	unsigned short totalTime = 90;

	bool isFlickering = false;
	bool canFlicker = true;

	int baseAlpha = 255 / totalFrames;

public:
	virtual void takeTimeFlicker();

	void makeFlicker();
	void makeSuperFlicker(int flickerTime);

	void reset();

	sf::Color flickerColor = sf::Color(255,255,255,255);
};

