#pragma once

#include "../SceneNode.h"
#include "../Button.h"

namespace States {
    enum ID {
		None,
		Main,
		HighScore,
		Load,
		NewGame,
		Settings,
		Pause,
		GameOver,
		Difficulty,
    };
};

class State : public SceneNode { // SceneNode to Store current state of the screen
public:
    typedef std::unique_ptr<State> Ptr;

	Ptr makeUnique(State* state);

	bool isDead=false;
	States::ID CurrentState=States::None;

	//void updateCurrent(Event& event, Vector2f& MousePos);
	//void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//void takeTimeCurrent(Time& dt);	
};