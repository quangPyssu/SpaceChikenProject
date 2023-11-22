#pragma once

#include "SceneNode.h"

#include "States/State.h"
#include "States/MainMenu.h"
#include "States/GameState.h"
#include "States/GameOverScreen.h"
#include "States/PauseMenu.h"
#include "States/LoadScreen.h"
#include "States/SettingMenu.h"
#include "States/PostGameMenu.h"
#include "States/Credit.h"

class StateSteak : private sf::NonCopyable { // StateSteak to Store all states of the screen
public: 
	StateSteak(RenderWindow& window);
	~StateSteak();

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

	void update(Event& event, Vector2f& MousePos);
	void draw(RenderTarget& target, RenderStates states) const;
	void takeTime();

private:
	std::vector<State::Ptr> Stack;
	State Dummy;

	void CreateState(States::ID &stateID);
	RenderWindow* window;
};