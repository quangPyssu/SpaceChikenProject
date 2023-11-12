#include "../SceneNode.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"

#include "Entity.h"

#pragma once

class Player : public Entity
{
	public:
	Player();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;
	void takeTimeCurrent() override;

	void resetGun();
	void resetSpecial();

	bool isFiring=false;
	bool isSpecialing = false;

	Vector2f PlayerCurPos;

	private:

		void atHalfHealth() override;
		void atQuarterHealth() override;
		void addDeathAnimation() override;
		Texture texturePlayer;
		short unsigned int reloadFrameID = 0;
		short unsigned int reloadFrameIDMax = 50;

		short unsigned int specialFrameID = 0;
		short unsigned int specialFrameIDMax = 200;

		short hasSpeacial = 100;

		friend class GameState;
};

