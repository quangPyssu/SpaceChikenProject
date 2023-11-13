#include "State.h"

State::State() {
	window = nullptr;
	textureStackID = ResourceManager::loadedTextures.size();
	soundStackID = ResourceManager::loadedSounds.size();
}

State::~State() {
	while (textureStackID < ResourceManager::loadedTextures.size())
	{		
		ResourceManager::unloadTexture(ResourceManager::loadedTextures.back());
		ResourceManager::loadedTextures.pop_back();
	}

	while (soundStackID < ResourceManager::loadedSounds.size())
	{
		ResourceManager::unloadSoundBuffer(ResourceManager::loadedSounds.back());
		ResourceManager::loadedSounds.pop_back();
	}

	if (music!=nullptr)
	{
		music->stop();		
		delete music;
	}

	if (parentState != nullptr)
	{
		if (parentState->music && parentState->music->getStatus()==sf::Music::Stopped)
		{
			parentState->music->play();
		}
		
	}	

	SubTitleList.clear();
}

State::State(RenderWindow& window) : window(&window){
	textureStackID = ResourceManager::loadedTextures.size();
	soundStackID = ResourceManager::loadedSounds.size();
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
	music->setVolume((float) musicVolume*masterVolume/100);
	music->play();
	music->setLoopPoints(sf::Music::TimeSpan(sf::seconds(offset), music->getDuration()));
}

void State::setMusicVolume()
{
	if (music != nullptr)
	{
		music->setVolume((float) musicVolume*masterVolume/100);
	}
}