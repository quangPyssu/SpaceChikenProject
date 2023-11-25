#include "../SceneNode.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"

#include "Entity.h"

#pragma once

class Player : public Entity
{
	public:
	Player();
	~Player();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;
	void takeTimeCurrent() override;

	void resetGun();
	void resetSpecial();

	bool isFiring=false;
	bool isSpecialing = false;

	Vector2f PlayerCurPos;
	int getCurrentWeapon() { return CurrentWeapon; }

	private:
		int CurrentWeapon = 0;

		void atHalfHealth() override;
		void atQuarterHealth() override;
		void addDeathAnimation() override;
		Texture texturePlayer;
		int reloadFrameID = 0;
		int reloadFrameIDMax = WeaponUnlocked[EquipedWeapon[CurrentWeapon]].ss;

		int specialFrameID = SpecialUnlocked[CurrentSpecial].ss-1;
		int specialFrameIDMax = SpecialUnlocked[CurrentSpecial].ss;


		//short hasSpeacial = 100;

		friend class GameState;
};

