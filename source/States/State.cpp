#include "State.h"

State::State() {
	window = nullptr;
}

State::~State() {
	for (auto& i : usedTextures)
	{
		//std::cout << "delete " << i << std::endl;
		ResourceManager::unloadTexture(i);
	}

	for (auto& i : usedSounds)
	{
		//std::cout << "delete " << i << std::endl;
		ResourceManager::unloadSoundBuffer(i);
	}
}

State::State(RenderWindow& window) : window(&window){
}


State::Ptr State::makeUnique(State* state)
{
	return std::unique_ptr<State>(state);
}

void State::playMusic(string ID, int offset)
{
	if (music != nullptr)
	{
		music->stop();
		delete music;
	}

	music = new sf::Music();
	music->openFromFile(ID);
	music->setLoop(true);
	music->setVolume(100);
	music->play();
	music->setLoopPoints(sf::Music::TimeSpan(sf::seconds(offset), music->getDuration()));
}