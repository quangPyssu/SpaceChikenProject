#include "Global.h"

namespace Constants {
    int modulo = 10;

    const int T = 3;
    const int weaponMax = 3;
    const int specialMax = 3;

    int CurrentWeapon1 = 0;
    int CurrentWeapon2 = 0;
    int CurrentSpecial = 0;

    sf::Vector2f PlayerHitboxSize = sf::Vector2f(50, 50);
    int PlayerMaxHP = 500;
    int CurrentLevel = 0;
    int CurrentWave = 0;

    std::pair <bool,short unsigned int> WeaponUnlocked[5] = { {true,50},{false,200},{false,15},{false,0},{false,0} };
    std::pair <bool,short unsigned int> SpecialUnlocked[5] = { {false,500},{false,3000},{false,4000},{false,0},{false,0} };

    int EquipedWeapon[2] = { 0,0 };

    short VortexId = 0;

    int breakTime = 300;
    int breakTimeMax = 300;

    const double pi = 3.14159265;
    double SCALE_X = (double)(sf::VideoMode::getDesktopMode().width) / (800);
    double SCALE_Y = (double)(sf::VideoMode::getDesktopMode().height) / (600);
    double SCALE = std::min(SCALE_X, SCALE_Y);
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    std::pair <double, double> OutScopeX = {-300*SCALE,1100 * SCALE };
    std::pair <double, double> OutScopeY = { -300 * SCALE,900 * SCALE };

    const float targetAspectRatio = 1920.0f / 1080.0f;

    sf::Vector2f Constants::WINDOW_SIZE = sf::Vector2f(800.0f, 600.0f);

    std::string GameMusicTrack[5][2] = { 
        {"Assets/Sounds/Music/lullaby_deserted_hell.ogg", "Assets/Sounds/Music/BeOfGoodCheer.ogg",},
        {"Assets/Sounds/Music/JinzoLament.ogg","Assets/Sounds/Music/magicJinzoStraw.ogg",},
		{"Assets/Sounds/Music/RetributionNight.ogg", "Assets/Sounds/Music/LoveMasterSpark.ogg",},
		{"Assets/Sounds/Music/WhoDoneIt.ogg", "Assets/Sounds/Music/Necrofantasia.ogg",},
		{"Assets/Sounds/Music/TheSeaOneHomePlanet.ogg", "Assets/Sounds/Music/PureFurries.ogg",} 
        };

    int GameMusicOffset[5][2] = { {0,12},{0,0},{38,0},{0,48},{54,0} };

    std::string MenuMusicTrack = "Assets/Sounds/Music/space_maiden_appear.ogg";   

    int masterVolume = 80;
    int musicVolume = 50;
    int soundVolume = 70;
    const int font_size_small = 20;
    const int font_size_medium = 30;
    const int font_size_large = 40;

    const int nothing = -999999999;

    bool IsPaused = false;

    const sf::Time TIME_PER_ANIME_FRAME = sf::seconds(0.6f);
    const float FRAME_PER_FRAME = 10;

    const sf::Vector2f ButtonTypeHead[3] = { sf::Vector2f(5,5), sf::Vector2f(125,112), sf::Vector2f(302,212) };
    const sf::Vector2f ButtonTypeTail[3] = { sf::Vector2f(95,95), sf::Vector2f(263,190), sf::Vector2f(287,298) };

    sf::Vector2f lastMousePos = sf::Vector2f(0, 0);
    sf::Vector2f dtMousePos = sf::Vector2f(0, 0);  

    bool DisplayHitbox = false;
};

namespace utility
{
    sf::Vector2f operator* (const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return sf::Vector2f(A.x * B.x, A.y * B.y);
    }

    sf::Vector2f operator*(const sf::Vector2f& A, const float& B)
    {
        return sf::Vector2f(A.x * B, A.y * B);
    }

    sf::Vector2f min(const sf::Vector2f& A, const sf::Vector2f& B)
    {
		return sf::Vector2f(std::min(A.x, B.x), std::min(A.y, B.y));
	}

    sf::Vector2f max(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return sf::Vector2f(std::max(A.x, B.x), std::max(A.y, B.y));
    }

    int randInt(int i)
    {
        return rand() % i;
    }
}

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
    sf::Color tran_Yellow = sf::Color(255, 255, 153, 128);
    sf::Color tran_Grey = sf::Color(128, 128, 128, 128);
};

namespace getScale
{
    sf::Vector2f getScaleMax(sf::Vector2f Oject, sf::Vector2f Target)
    {
        double res = std::max(Target.x / Oject.x, Target.y / Oject.y);
        sf::Vector2f res2 = sf::Vector2f(res, res);
        return res2;
    }

    sf::Vector2f getScaleMin(sf::Vector2f Oject, sf::Vector2f Target)
    {
        double res = std::min(Target.x / Oject.x, Target.y / Oject.y);
        sf::Vector2f res2 = sf::Vector2f(res, res);
        return res2;
    }

sf::Vector2f getScaleStretch(sf::Vector2f Oject, sf::Vector2f Target)
	{
        sf::Vector2f res = sf::Vector2f(Target.x / Oject.x, Target.y / Oject.y);
		return res;
	}


}

namespace ResourceManager
{
    std::vector<std::string> loadedTextures;
    std::vector<std::string> loadedSounds;

    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;

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
            } else throw std::runtime_error("Failed to load font: " + ID);
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

        if (it != textures.end()) return *it->second; else
        {
            std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
            if (texture->loadFromFile("Assets/Textures/" + ID)) {
                loadedTextures.push_back(ID);
                textures.emplace(ID, texture);
                return *(texture);
            }
            else throw std::runtime_error("Failed to load texture: " + ID);
        }
    }    

    sf::SoundBuffer& getSoundBuffer(const std::string& ID)
    {
		auto it = soundBuffers.find(ID);

        if (it != soundBuffers.end()) return *it->second; else
        {
			std::shared_ptr <sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
            if (buffer->loadFromFile("Assets/Sounds/" + ID))
            {
                loadedSounds.push_back(ID);
				soundBuffers.emplace(ID, buffer);
				return *(buffer);
			} else throw std::runtime_error("Failed to load sound effect: " + ID);
		}
	}

    void unloadSoundBuffer(const std::string& ID)
    {
        auto it = soundBuffers.find(ID);

        if (it != soundBuffers.end())
        {
            //std::cout << " Unloading Sound: " << ID << "\n";
            soundBuffers.erase(it);
        }
    }

    void unloadTexture(const std::string& ID)
    {
		auto it = textures.find(ID);

        if (it != textures.end())
        {
            //std::cout << " Unloading texture: " << ID << "\n";
            textures.erase(it);
        }
    }
}
