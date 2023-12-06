#pragma once

#include "../SceneNode.h"
#include "../Button.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"
#include "../Tools/SubTitle.h"
#include <fstream>

namespace States {
    enum ID {
		None,
		Main,
		HighScore,
		Load,
		NewGame,
		LevelComplete,
		Setting,
		Pause,
		GameOver,
		Difficulty,
		KillMe,
		Credit
    };
};

class CurrentData;

class State : public SceneNode { // SceneNode to Store current state of the screen
public:
	State();
	~State();
	State(RenderWindow& window);

    typedef std::unique_ptr<State> Ptr;

	Ptr makeUnique(State* state);
	States::ID CurrentState=States::None;

	State* parentState=nullptr;

	sf::Music* music=nullptr;

	void playMusic(string ID,int offset);
	void setMusicVolume();

protected:
	RenderWindow* window=nullptr;

	int textureStackID;
	int soundStackID;
	

	vector <SubTitle*> SubTitleList;

	sf::View shakeView(float intensity);
	float ShakeDuration = 0;
	View originalView;
};

class CurrentData {
private:
	static ifstream fin;
	static ofstream fout;

public:
	static void getData();
	static void writeData();
};