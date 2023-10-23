#pragma once

#include "../SceneNode.h"
#include "../Button.h"
#include "../Animation/Animation.h"

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
		KillMe
    };
};

class State : public SceneNode { // SceneNode to Store current state of the screen
public:
    typedef std::unique_ptr<State> Ptr;

	Ptr makeUnique(State* state);
	States::ID CurrentState=States::None;

	State* parentState=nullptr;
};