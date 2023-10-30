#pragma once
#include "../SceneNode.h"

class WarningZone :  public SceneNode
{
	public:
		WarningZone();
	~WarningZone();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void takeTimeCurrent() override;	

	void addWarningZone(sf::RectangleShape shape, int timeToLive=80);
	void addWarningZone(sf::CircleShape shape, int timeToLive=80);

	private:
		vector <pair <RectangleShape,int>> RectangleWarningZone; //int is the time to live
		vector <pair <CircleShape,int>> CircleWarningZone;		//int is the time to live	
};

