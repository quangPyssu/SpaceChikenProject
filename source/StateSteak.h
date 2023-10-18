#pragma once

#include "SceneNode.h"

#include "States/State.h"
#include "States/MainMenu.h"
#include "States/GameState.h"

class StateSteak : private sf::NonCopyable { // StateSteak to Store all states of the screen
public: 
	StateSteak();

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

	void update(Event& event, Vector2f& MousePos);
	void draw(RenderTarget& target, RenderStates states) const;
	void takeTime(Time& dt);

private:
	std::vector<State::Ptr> Stack;
	State Dummy;

	void CreateState(States::ID &stateID);
};