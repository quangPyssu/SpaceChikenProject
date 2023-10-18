#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text) // defualt constructor
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(Colors::grey);

	//label.setFont(ResourceManager::getFont("ArialTh"));
	label.setFont(ResourceManager::getFont("neuro"));
	label.setString(text);
	label.setCharacterSize(size.y / 2);
	label.setFillColor(Colors::black);
	label.setPosition(position.x + size.x / 2 - label.getGlobalBounds().width / 2, position.y + size.y / 2 - label.getGlobalBounds().height / 2);
	
}

Button::Button(const sf::Vector2f& position, int ButtonType, const std::string& text)
{
	/*int x = (ButtonType-1) % 3;
	int y = (ButtonType-1) / 3;

	shape.setPosition(position);
	shape.setSize(Constants::ButtonTypeTail[x]-);
	shape.setSize(size);
	shape.setFillColor(Colors::grey);

	label.setFont(ResourceManager::getFont("neuro"));
	label.setString(text);
	label.setCharacterSize(size.y / 2);
	label.setFillColor(Colors::black);
	label.setPosition(position.x + size.x / 2 - label.getGlobalBounds().width / 2, position.y + size.y / 2 - label.getGlobalBounds().height / 2);

	texture = ResourceManager::getTexture("Metal-Buttons.png");

	shape.setTextureRect(sf::IntRect(Constants::ButtonTypeHead[2].x, Constants::ButtonTypeHead[2].y,
		Constants::ButtonTypeTail[2].x, Constants::ButtonTypeTail[2].y));
	shape.setTexture(&texture);*/
}

void Button::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(label, states);
}	

void Button::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (isLeftClicked(event, MousePos)) {
		shape.setFillColor(Colors::red);
	}
	else if (isRightClicked(event, MousePos)) {
		shape.setFillColor(Colors::blue);
	}
	else if (isHovered(event, MousePos)) {
		shape.setFillColor(Colors::green);
	}
	else {
		shape.setFillColor(Colors::grey);
	}
}

void Button::takeTimeCurrent(Time& dt)
{
}

bool Button::isLeftClicked(Event& event, Vector2f& MousePos) {
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (MousePos.x >= shape.getPosition().x && MousePos.x <= shape.getPosition().x + shape.getSize().x && MousePos.y >= shape.getPosition().y && MousePos.y <= shape.getPosition().y + shape.getSize().y) {
			return true;
		}
	}
	return false; 
}

bool Button::isRightClicked(Event& event, Vector2f& MousePos) { 
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
		if (MousePos.x >= shape.getPosition().x && MousePos.x <= shape.getPosition().x + shape.getSize().x && MousePos.y >= shape.getPosition().y && MousePos.y <= shape.getPosition().y + shape.getSize().y) {
			return true;
		}
	}
	return false; 
}

bool Button::isHovered(Event& event, Vector2f& MousePos) {
	if (MousePos.x >= shape.getPosition().x && MousePos.x <= shape.getPosition().x + shape.getSize().x && MousePos.y >= shape.getPosition().y && MousePos.y <= shape.getPosition().y + shape.getSize().y) {
		return true;
	}
	return false; 
}