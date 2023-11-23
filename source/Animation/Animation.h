#include "SFML/Graphics.hpp"
#include "../SceneNode.h"

#pragma once

class Animation : public SceneNode
{
private:
	unsigned short animationFrameID;
	//The higher the value, the slower the animation REVERSE for moving loop animation
	unsigned short animationSpeed;
	unsigned short currentFrame=1;
	//To make things easier, each image file will contain 1 animation. So that the frame heights are the same.
	unsigned short Height, Width;
	//We can find this by dividing the width of the image by the frame width.
	unsigned short totalFrames;

	unsigned short totalWidth = 0;

	unsigned short totalTime = 0;

	unsigned short floorCnt, currentFloor, FramePerFloor;
	unsigned short widthCnt;

	sf::Sprite sprite;

	sf::Texture texture;

	sf::Vector2f divation = { 0,0 };
	float rotationDivation = 0;

	bool isRootSet = true;
	bool isPingPong = false;
	bool hasLimitedTime = false;

	bool RotationDependent = true;

	int pingPongDirection = 1;
	int resetFrame = 0;

public:
	Animation(unsigned short animationSpeed, unsigned short widthCnt, unsigned short floorCnt,double Scale,Vector2f Position, Vector2f Origin, const std::string& i_texture_location);//for frame based animation
	Animation(unsigned short animationSpeed, unsigned short widthCnt, unsigned short floorCnt, double Scale, Vector2f Position, Vector2f Origin, Vector2f divation, const std::string& i_texture_location);
	Animation(unsigned short animationSpeed, unsigned short widthCnt, unsigned short floorCnt, double Scale, Vector2f Position, Vector2f Origin, Vector2f divation, const std::string& i_texture_location, int TotalTime);

	Animation(unsigned short animationSpeed, float FrameWidth, double Scale,Vector2f Position, Vector2f Origin, const std::string& i_texture_location);//for moving loop animation

	bool isAnimationFinished();
	

	void takeTimeCurrent() override;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPosition(Vector2f pos) ;
	void setOrigin(Vector2f origin) ;
	void setScale(Vector2f scale) ;
	void setDivation(Vector2f divation) ;
	void setFlickerColor(sf::Color color) ;
	void setTotalTime(int totalTime) { this->totalTime = totalTime; }

	Vector2f getSize();

	void setRotationDivation(float rotationDivation);

	void setResetFrame(int resetFrame);
	void makePingPong();

	void setTransparency(float transparency);
	void setCurrentFrame(int currentFrame);

	void reset();
};

