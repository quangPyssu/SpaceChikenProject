#include "SubTitle.h"

SubTitle::SubTitle(sf::Vector2f position, sf::Vector2f size, sf::Color bgColor, 
	sf::Vector2f labelPos, int labelSize, sf::Color labelColor, std::string label,std::string font = "ArialTh", int timerEnd=-1)
{
	background.setPosition(position);
	background.setSize(size);
	background.setFillColor(bgColor);

	totalHeight = size.y;
	totalWidth = size.x;

	if (font == "") font = "ArialTh";

	this->label.setFont(ResourceManager::getFont(font));

	this->label.setString(label);
	this->label.setCharacterSize(labelSize*SCALE);
	this->label.setFillColor(labelColor);
	this->label.setPosition(position+(size*labelPos));

	this->baseBGAlpha = bgColor.a;
	this->baseLabelAlpha = labelColor.a;

	this->timerEnd = timerEnd;
	this->timerEndBase = timerEnd;
}

void SubTitle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(label, states);
}	

void SubTitle::takeTimeCurrent()
{
	if (timerEnd != -1)
	{
		if (timerEnd > 0) timerEnd--;

		setTranparency((float) timerEnd/timerEndBase);
	}
}

void SubTitle::setTranparency(float alpha)
{	
	background.setFillColor(sf::Color(background.getFillColor().r, background.getFillColor().g, background.getFillColor().b
		, alpha*baseBGAlpha));
	label.setFillColor(sf::Color(label.getFillColor().r, label.getFillColor().g, label.getFillColor().b
		, alpha*baseLabelAlpha));
}

SubTitle::~SubTitle()
{
}

