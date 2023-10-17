#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define ff first
#define ss second

#define null NULL

namespace Constants
{
    extern int modulo;
    extern const int T;

    extern const double pi;
    extern const double SCALE_X;
    extern const double SCALE_Y;
    extern const double SCALE;
    extern const sf::Time TIME_PER_FRAME;
    extern const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;

    extern const float targetAspectRatio;

    extern const float EDGE_THICKNESS;
    extern const sf::Vector2f BUTTON_SIZE;
    extern const sf::Vector2f TEXTBOX_SIZE;

    extern const int nothing;

    extern const sf::Time TIME_PER_ANIME_FRAME;
    extern const float FRAME_PER_FRAME;

    enum states {IDLE, HOVER , PRESSED , ACTIVE};

    enum TextAlign {Left,Middle,Right};
};

namespace Var {
    
}

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
};

namespace ResourceManager
{

    static std::map<std::string, sf::Font> fonts;
    static std::map<std::string, sf::Texture> textures;

    sf::Font& getFont(const std::string& ID);
    sf::Texture& getTexture(const std::string& ID);
}
