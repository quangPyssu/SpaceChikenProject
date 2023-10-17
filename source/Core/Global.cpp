#include "Global.h"

namespace Constants {
    int modulo = 10;

    const int T = 3;

    const double pi = 3.14159265;
    const double SCALE_X = (double)(sf::VideoMode::getDesktopMode().width)/(800) ;
    const double SCALE_Y = (double)(sf::VideoMode::getDesktopMode().height)/(600) ;
    const double SCALE = std::min(SCALE_X, SCALE_Y);
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width/3*2;
    const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height/3*2;

    const float targetAspectRatio = 1920.0f / 1080.0f;

    const int font_size_small = 20;
    const int font_size_medium = 30;
    const int font_size_large = 40; 

    const int nothing=-999999999;

    const sf::Time TIME_PER_ANIME_FRAME = sf::seconds(0.6f);
    const float FRAME_PER_FRAME=10;
};

namespace Colors {
    sf::Color trans = sf::Color::Transparent;
    sf::Color white = sf::Color::White;
    sf::Color black = sf::Color::Black;
    sf::Color red = sf::Color::Red;
    sf::Color cyan = sf::Color::Cyan;
    sf::Color yellow = sf::Color::Yellow;
    sf::Color blue = sf::Color::Blue;
    sf::Color green = sf::Color::Green;
    sf::Color light_yellow = sf::Color(255,255,153);
    sf::Color orange = sf::Color(255, 83, 0);
    sf::Color grey = sf::Color(128,128,128);
    sf::Color light_grey = sf::Color(192, 192, 192);
    sf::Color pink = sf::Color(214, 87, 117);
    sf::Color purple = sf::Color(128, 0, 128);
    sf::Color Back_Ground_Color = white;
    sf::Color Chosen_Color = cyan;
    sf::Color Delete_Color = red;
    sf::Color Insert_Color = orange;
    sf::Color Search_Color = pink;
    sf::Color Default_Color = black;
};

namespace ResourceManager
{
    sf::Font& getFont(const std::string& ID)
    {
      auto it = fonts.find(ID);

        if (it != fonts.end()) return it->second; else
        {
            sf::Font font;
            if (font.loadFromFile("Assets/Fonts/" + ID + ".ttf"))
            {
                fonts.emplace(ID, font);
                return fonts[ID];
            }
        }
    }

    struct FontDestructor
    {
        ~FontDestructor()
        {
            fonts.clear(); 
            textures.clear();
        }
    };

    static FontDestructor destructor; 

    sf::Texture& getTexture(const std::string& ID)
    {
        auto it = textures.find(ID);

        if (it != textures.end()) return it->second; else
        {
            sf::Texture texture;
            if (texture.loadFromFile("Assets/Textures/" + ID ))
            {
                textures.emplace(ID, texture);
                return textures[ID];
            }
        }
    }



    
}
