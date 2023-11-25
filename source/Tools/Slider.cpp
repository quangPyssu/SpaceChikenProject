#include "Slider.h"

Slider::Slider(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color bgColor, std::string name,int& Base,int BaseMax)
{
	position = position* Vector2f(SCALE,SCALE);
	size = size* Vector2f(SCALE,SCALE);

	background.setPosition(position);
	background.setSize(size);
	background.setFillColor(bgColor);

	bar.setPosition(position);
	bar.setSize(size);
	bar.setFillColor(fillColor);

	totalHeight = size.y;
	totalWidth = size.x;

	this->Base = &Base;
	this->BaseMax = BaseMax;

	label.setFont(ResourceManager::getFont("ArialTh"));

	label.setString(name);
	label.setCharacterSize(size.y / 1.2);
	label.setFillColor(Colors::white);
	label.setPosition(position.x - label.getGlobalBounds().width*1.1, position.y + size.y / 2 - label.getGlobalBounds().height / 2);

	percent.setFont(ResourceManager::getFont("ArialTh"));

	string s = std::to_string((int) *this->Base*100/BaseMax);

	bar.setScale({(float) *this->Base/BaseMax,1 });

	percent.setString(s);
	percent.setCharacterSize(size.y / 1.2);
	percent.setFillColor(Colors::black);
	percent.setPosition(position.x + size.x/2, position.y + size.y / 3 - label.getGlobalBounds().height / 2);
}

void Slider::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(bar, states);
	target.draw(label, states);
	target.draw(percent, states);
}	

void Slider::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			if (background.getGlobalBounds().contains(MousePos))
			{
				isPressed = true;
			}
		}
	}
	else if (event.type == Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			isPressed = false;
		}
	}

	if (isPressed)
	{
		if (MousePos.x > background.getPosition().x && MousePos.x <= background.getPosition().x + background.getSize().x)
		{
			*Base = (MousePos.x - background.getPosition().x) / background.getSize().x * BaseMax;
			string s = std::to_string(*this->Base*100 / BaseMax);
			percent.setString(s);
			bar.setScale({(float) *this->Base / BaseMax,1 });
		}
	}
	else
	{
		bar.setScale({ (float)*this->Base / BaseMax,1 });
	}
}