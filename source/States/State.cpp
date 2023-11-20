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

sf::View State::shakeView( float intensity) {
	sf::View resultView = originalView;
	resultView.move(std::rand() % static_cast<int>(intensity) - intensity / 2,	std::rand() % static_cast<int>(intensity) - intensity / 2);
	return resultView;
}

std::ifstream CurrentData::fin;
std::ofstream CurrentData::fout;

void CurrentData::getData()
{
	fin.open("Data/Current.inp");
	fin >> Constants::CurrentLevel;

	for (int i = 0; i < Constants::weaponMax; i++) fin >> Constants::WeaponUnlocked[i].first;
	for (int i = 0; i < Constants::specialMax; i++) fin >> Constants::SpecialUnlocked[i].first;

	WeaponUnlocked[0].first = true;

	fin.close();

	//delete later	

//  0 1 < -- Level, Wave
//
//	1 0  < -- bool for Weapon Unlocked  // basic is alway on so no reading
// 	1 0 0  < -- bool for Special Unlocked
}

void CurrentData::writeData()
{
	fout.open("Data/Current.inp");
	fout.clear();
	fout << Constants::CurrentLevel << endl;

	for (int i = 0; i < Constants::weaponMax; i++) fout << Constants::WeaponUnlocked[i].first << " ";	fout << endl;
	for (int i = 0; i < Constants::specialMax; i++) fout << Constants::SpecialUnlocked[i].first << " ";	fout << endl;

	fout.close();
}