#include "ProgressBar.h"

ProgressBar::ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color bgColor, std::string name,int& Base,int& BaseMax)
{
	background.setPosition(position);
	background.setSize(size);
	background.setFillColor(bgColor);

	bar.setPosition(position);
	bar.setSize(size);
	bar.setFillColor(fillColor);

	totalHeight = size.y;
	totalWidth = size.x;

	this->Base = &Base;
	this->BaseMax = &BaseMax;

	label.setFont(ResourceManager::getFont("ArialTh"));
	//label.setFont(ResourceManager::getFont("neuro"));

	label.setString(name);
	label.setCharacterSize(size.y / 1.2);
	label.setFillColor(Colors::black);
	label.setPosition(position.x + size.x / 2 - label.getGlobalBounds().width / 2, position.y + size.y / 2 - label.getGlobalBounds().height / 2);
}

void ProgressBar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(bar, states);
	target.draw(label, states);
}	

void ProgressBar::takeTimeCurrent()
{
	bar.setSize(sf::Vector2f(totalWidth * (float(*Base) / float(*BaseMax)), totalHeight));
}