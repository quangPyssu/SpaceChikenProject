#include "SFML/Graphics.hpp"
#include "../SceneNode.h"

#pragma once

class Animation : public SceneNode
{
private:
	unsigned short animationFrameID;
	//The higher the value, the slower the animation.
	unsigned short animationSpeed;
	unsigned short currentFrame;
	//To make things easier, each image file will contain 1 animation. So that the frame heights are the same.
	unsigned short frameWidth;
	//We can find this by dividing the width of the image by the frame width.
	unsigned short totalFrames;

	sf::Sprite sprite;

	sf::Texture texture;
public:
	Animation(unsigned short animationSpeed, unsigned short frameWidth, unsigned short floorCnt,double Scale,Vector2f Position, Vector2f Origin, const std::string& i_texture_location);

	unsigned short floorCnt,currentFloor,FramePerFloor;

	double floorHeight;

	void takeTimeCurrent() override;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

	void setPosition(Vector2f pos) ;
	void setOrigin(Vector2f origin) ;
	void setScale(Vector2f scale) ;
	void setRotation(float rotation) ;

	void reset();
};

