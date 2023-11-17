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
		RectangleWarningZone[i].ff.setOutlineColor(RectangleWarningZone[i].ff.getOutlineColor() + sf::Color(0, 0, 0, 1));

		if (RectangleWarningZone[i].ss <= 0)
		{
			RectangleWarningZone.erase(RectangleWarningZone.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < CircleWarningZone.size(); i++)
	{
		CircleWarningZone[i].ss--;
		CircleWarningZone[i].ff.setOutlineColor(CircleWarningZone[i].ff.getOutlineColor() + sf::Color(0, 0, 0, 1));

		if (CircleWarningZone[i].ss <= 0)
		{
			CircleWarningZone.erase(CircleWarningZone.begin() + i);
			i--;
		}
	}
}

void WarningZone::addWarningZone(sf::RectangleShape shape, int timeToLive)
{
	shape.setOutlineColor(shape.getOutlineColor() - sf::Color(0, 0, 0, 255));
	RectangleWarningZone.push_back(make_pair(shape, timeToLive));
}

void WarningZone::addWarningZone(sf::CircleShape shape, int timeToLive)
{
	shape.setOutlineColor(shape.getOutlineColor() - sf::Color(0, 0, 0, 255));
	CircleWarningZone.push_back(make_pair(shape, timeToLive));
}