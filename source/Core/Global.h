#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <queue>

#define ff first
#define ss second

#define null NULL

typedef std::pair<int,int> ii;

namespace Constants
{
    extern int modulo;
    extern const int T;

    extern const double pi;
    extern double SCALE_X;
    extern double SCALE_Y;
    extern double SCALE;
    extern const sf::Time TIME_PER_FRAME;
    extern sf::Vector2f WINDOW_SIZE;

    extern std::string GameMusicTrack[5][2];
    extern std::string MenuMusicTrack;

    extern int GameMusicOffset[5][2];

    extern int masterVolume;
    extern int musicVolume;
    extern int soundVolume;

    extern std::pair <double, double> OutScopeX, OutScopeY;

    extern const float targetAspectRatio;
    extern bool IsPaused;

    extern const float EDGE_THICKNESS;
    extern const sf::Vector2f BUTTON_SIZE;
    extern const sf::Vector2f TEXTBOX_SIZE;

    extern sf::Vector2f dtMousePos;
    extern sf::Vector2f lastMousePos;

    extern const int nothing;

    extern const sf::Time TIME_PER_ANIME_FRAME;
    extern const float FRAME_PER_FRAME;

    extern const sf::Vector2f ButtonTypeHead[3];
    extern const sf::Vector2f ButtonTypeTail[3];

    extern int PlayerMaxHP;
    extern int CurrentLevel;
    extern int CurrentWave;

    extern sf::Vector2f PlayerHitboxSize;

    extern const int weaponMax;
    extern const int specialMax;
    extern int CurrentWeapon1;
    extern int CurrentWeapon2;
    extern int CurrentSpecial;

    extern int EquipedWeapon[2];

    extern std::pair <bool,short unsigned int> WeaponUnlocked[5];  // unlocked, max cooldown
    extern std::pair <bool,short unsigned int> SpecialUnlocked[5]; // unlocked, max cooldown

    extern int breakTime;
    extern int breakTimeMax;

    enum TextAlign {Left,Middle,Right};       

    extern bool DisplayHitbox;
};

namespace Colors
{
    extern sf::Color trans;
    extern sf::Color white;
    extern sf::Color black;
    extern sf::Color red;
    extern sf::Color blue;
    extern sf::Color green;
    extern sf::Color cyan;
    extern sf::Color yellow;
    extern sf::Color orange;
    extern sf::Color light_yellow;
    extern sf::Color grey;
    extern sf::Color pink;
    extern sf::Color purple;
    extern sf::Color Back_Ground_Color;
    extern sf::Color Default_Color;
    extern sf::Color Chosen_Color;
    extern sf::Color Delete_Color;
    extern sf::Color Insert_Color;
    extern sf::Color Search_Color;
    extern sf::Color tran_Yellow;
    extern sf::Color tran_Grey;
};

namespace getScale
{
    sf::Vector2f getScaleMax(sf::Vector2f Object, sf::Vector2f Target); //fill
    sf::Vector2f getScaleMin(sf::Vector2f Object, sf::Vector2f Target); //fit
    sf::Vector2f getScaleStretch(sf::Vector2f Object, sf::Vector2f Target); //Stretch
}

namespace utility
{
    sf::Vector2f operator *(const sf::Vector2f& A, const sf::Vector2f& B);
    sf::Vector2f operator *(const sf::Vector2f& A, const float & B);
    sf::Vector2f min(const sf::Vector2f& A, const sf::Vector2f& B);
    sf::Vector2f max(const sf::Vector2f& A, const sf::Vector2f& B);
    int randInt(int i);
}

namespace ResourceManager
{
    extern std::vector<std::string> loadedTextures;
    extern std::vector<std::string> loadedSounds;

    extern std::unordered_map<std::string, sf::Font> fonts;
    extern std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    extern std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;

    sf::Font& getFont(const std::string& ID);
    sf::Texture& getTexture(const std::string& ID);
    sf::SoundBuffer& getSoundBuffer(const std::string& ID);

    void unloadSoundBuffer(const std::string& ID);
    void unloadTexture(const std::string& ID);
}
