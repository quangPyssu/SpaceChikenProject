#include "WarningZone.h"

WarningZone::WarningZone()
{
}

WarningZone::~WarningZone()
{
	RectangleWarningZone.clear();
	CircleWarningZone.clear();
}

void WarningZone::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < RectangleWarningZone.size(); i++) target.draw(RectangleWarningZone[i].ff);
	for (int i = 0; i < CircleWarningZone.size(); i++) target.draw(CircleWarningZone[i].ff);
}

void WarningZone::takeTimeCurrent()
{
	for (int i = 0; i < RectangleWarningZone.size(); i++)
	{
		RectangleWarningZone[i].ss--;
		if (RectangleWarningZone[i].ss <= 0)
		{
			RectangleWarningZone.erase(RectangleWarningZone.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < CircleWarningZone.size(); i++)
	{
		CircleWarningZone[i].ss--;
		if (CircleWarningZone[i].ss <= 0)
		{
			CircleWarningZone.erase(CircleWarningZone.begin() + i);
			i--;
		}
	}
}

void WarningZone::addWarningZone(sf::RectangleShape shape, int timeToLive)
{
	RectangleWarningZone.push_back(make_pair(shape, timeToLive));
}

void WarningZone::addWarningZone(sf::CircleShape shape, int timeToLive)
{
	CircleWarningZone.push_back(make_pair(shape, timeToLive));
}