#pragma once

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#include<cstdlib>
#include<ctime>
#include<vector>
#include<sstream>


class Game
{
private:
	//Private Data and Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game Logic
	bool menuState;
	bool gameOver;
	bool creditState;
	bool newGame;
	bool arrowClick;
	bool spaceClick;
	bool enterClick;

	//Gameplay variables
	int points;
	float jumpHeight;
	float initJumpPos;
	sf::Vector2f jumpSpeed;
	sf::Vector2f jumpVelocity;
	sf::Vector2f gravity;
	sf::Vector2f gravityVelocity;
	bool jumpState;

	//Variables
	sf::Vector2u windowSize;
	FILE* file;
	enum class menuOptions : unsigned int {start = 0, credit = 1,exit = 2};
	menuOptions options;

	//Game Objects
	sf::RectangleShape wall;
	sf::RectangleShape wallMirror;
	sf::RectangleShape bird;
	sf::RectangleShape bg;
	std::vector<sf::RectangleShape> wallsDown;
	std::vector<sf::RectangleShape> wallsup;

	//Game Textures
	sf::Texture wallTexture;
	sf::Texture birdTexture;
	sf::Texture bgTexture;

	//Game Sounds
	sf::Music bgMusic;
	sf::SoundBuffer clickSound_Buffer;
	sf::Sound clickSound;

	//Game Fonts
	sf::Font font;

	//Game Texts
	sf::Text textStart;
	sf::Text textExit;
	sf::Text textCredit;
	sf::Text textHighScore;
	sf::Text textCreditinfo;
	sf::Text textPoints;
	sf::Text textGameOver;

	//Private Functions
	void initWindow();
	void checkHighScore();
	void initSprites();
	void initTextures();
	void initSounds();
	void initFonts();
	void initTexts();
		
public:
	//Constructor and Destructor
	Game();
	virtual ~Game();

	//Access
	const bool running() const;
	const bool checkMenu() const;
	const bool checkCredit() const;

	//Public Functions
	void pollEvents();
	void renderMenu();
	void renderCredit();
	void renderGame();
	void drawWindow();
	void display();
	void gameUpdate();
	void gamePlay();
};