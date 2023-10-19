#include "Player.h"

Player::Player()
{
	hitbox.setOutlineThickness(1);

	texturePlayer = ResourceManager::getTexture("Battlecruiser_Base.png");
	

	hitbox.setSize(sf::Vector2f(texturePlayer.getSize().x/3, texturePlayer.getSize().y/2));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);

	{
		animations.push_back(new Animation(10, 68, 6, 1, { 0,0 }, { 0,0.5 }, "FireJet.png"));
		animations.back()->setRotation(90);
		animations.back()->PushToObject(animations.back(), this);

		animationPos.push_back(Vector2f(0, texturePlayer.getSize().y / 4));
	}

	{
		sprites.push_back(new SpriteOnly("Battlecruiser_Base.png"));
		sprites.back()->PushToObject(sprites.back(), this);

		spritePos.push_back(Vector2f(0, 0));

		sprites.back()->setOrigin({ 0.5, 0.5 });
	}
}

Player::~Player()
{

}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(hitbox);
}

void Player::updateCurrent(Event& event, Vector2f& MousePos)
{
	setPosition(MousePos);
	hitbox.setPosition(getPosition());

	for (int i = 0; i < animations.size(); i++)	animations[i]->setPosition(getPosition()+animationPos[i]);

	for (int i = 0 ;i < sprites.size(); i++) sprites[i]->setPosition(getPosition() + spritePos[i]);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		//cout << "Player::updateC
	}
}

void Player::takeTimeCurrent()
{
}

