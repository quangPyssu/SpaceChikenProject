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
    extern const double SCALE_X;
    extern const double SCALE_Y;
    extern const double SCALE;
    extern const sf::Time TIME_PER_FRAME;
    extern sf::Vector2f WINDOW_SIZE;

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

    extern int breakTime;
    extern int breakTimeMax;

    enum TextAlign {Left,Middle,Right};    
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
};

namespace getScale
{
    sf::Vector2f getScaleMax(sf::Vector2f Object, sf::Vector2f Target); //fill
    sf::Vector2f getScaleMin(sf::Vector2f Object, sf::Vector2f Target); //fit
    sf::Vector2f getScaleStretch(sf::Vector2f Object, sf::Vector2f Target); //Stretch
}

namespace ResourceManager
{
    static std::unordered_map<std::string, sf::Font> fonts;
    static std::unordered_map<std::string, sf::Texture> textures;
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

    sf::Font& getFont(const std::string& ID);
    sf::Texture& getTexture(const std::string& ID);
    sf::SoundBuffer& getSoundBuffer(const std::string& ID);

    void unloadSoundBuffer(const std::string& ID);
    void unloadTexture(const std::string& ID);
}
