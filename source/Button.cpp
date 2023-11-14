#include "Button.h"

Button::Button(const sf::Vector2f position, const sf::Vector2f& size, const std::string& text) // defualt constructor
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

void Button::setSpriteOnly(const std::string& textureName)
{
	sprite = new SpriteOnly(textureName);
	sprite->setPosition(shape.getPosition());
	sprite->setScale(getScale::getScaleMin(sprite->getSize(), shape.getSize()).x);
	PushToObject(sprite, this);	
}

bool Button::isLeftClicked(Event& event, Vector2f& MousePos) { if (!isInteractable) return false;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (MousePos.x >= shape.getPosition().x && MousePos.x <= shape.getPosition().x + shape.getSize().x && MousePos.y >= shape.getPosition().y && MousePos.y <= shape.getPosition().y + shape.getSize().y) {
			return true;
		}
	}
	return false; 
}

bool Button::isRightClicked(Event& event, Vector2f& MousePos) {	if (!isInteractable) return false;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
		if (MousePos.x >= shape.getPosition().x && MousePos.x <= shape.getPosition().x + shape.getSize().x && MousePos.y >= shape.getPosition().y && MousePos.y <= shape.getPosition().y + shape.getSize().y) {
			return true;
		}
	}
	return false; 
}

bool Button::isHovered(Event& event, Vector2f& MousePos) {	if (!isInteractable) return false;
	if (MousePos.x >= shape.getPosition().x && MousePos.x <= shape.getPosition().x + shape.getSize().x && MousePos.y >= shape.getPosition().y && MousePos.y <= shape.getPosition().y + shape.getSize().y) {
		return true;
	}
	return false; 
}