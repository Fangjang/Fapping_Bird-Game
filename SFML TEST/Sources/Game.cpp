#include"Game.h"

//Private Functions
// 
//Initialize Window
void Game::initWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Fapping Bird", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->menuState = true;
	this->creditState = false;
	this->gameOver = false;
	this->newGame = true;

	this->options = menuOptions::start;
	this->arrowClick = false;
	this->spaceClick = false;
	this->enterClick = false;
	this->windowSize = this->window->getSize();

	this->points = 00;
	this->gravity = sf::Vector2f(0.f, 5.f);
	this->gravityVelocity = sf::Vector2f(0.f, 0.f);
	this->jumpSpeed = sf::Vector2f(0.f, -5.f);
	this->jumpVelocity = sf::Vector2f(0.f, 0.f);
	this->jumpHeight = 80.f;
	this->jumpState = false;
}

//Initialize sprites
void Game::initSprites()
{
	//Setting background's Sprite size and
	//its Position in the middle of the window
	this->bg.setSize(sf::Vector2f(static_cast<float>(this->windowSize.x),
		static_cast<float>(this->windowSize.y)));
	this->bg.setPosition(static_cast<float>(this->windowSize.x) / 2, 
		static_cast<float>(this->windowSize.y) / 2);
	this->bg.setOrigin((this->bg.getSize().x) / 2, (this->bg.getSize().y) / 2);

	//Setting the bird's size and position
	this->bird.setSize(sf::Vector2f(50.f, 35.f));
	this->bird.setPosition(sf::Vector2f( 50.f, (this->windowSize.y)/2 - 120));
	this->bird.setOrigin(this->bird.getSize().x / 2 , this->bird.getSize().y / 2);

	//Setting the Wall's Spirte size
	this->wall.setSize(sf::Vector2f(100.f, 500.f));
	this->wall.setPosition(sf::Vector2f(800.f, 350.f));
//	this->wall.setOrigin(sf::Vector2f(50.f, 250.f));

	this->wallMirror.setSize(sf::Vector2f(100.f, 500.f));
	this->wallMirror.setPosition(sf::Vector2f(800.f, 250.f));
	this->wallMirror.setOrigin(0.f, 500.f);
}

//Initialize and set Textures to sprites
void Game::initTextures()
{
	//Loading and setting background's Texure
	this->bgTexture.loadFromFile("Textures/bg.png");
	this->bg.setTexture(&(this->bgTexture));

	//Loading and setting bird's Textures
	this->birdTexture.loadFromFile("Textures/bird.png");
	this->bird.setTexture(&(this->birdTexture));

	//Loading and setting the wall's texture
	this->wallTexture.loadFromFile("Textures/wall.png");
	this->wall.setTexture(&(this->wallTexture));

	//Setting and mirroring the texture of upper wall
	this->wallMirror.setTexture(&(this->wallTexture));
	this->wallMirror.setTextureRect(sf::IntRect(0, 500, 100, -500));
}

//Initialize Sound
void Game::initSounds()
{
	this->bgMusic.openFromFile("Sounds/musicBg.wav");
	this->bgMusic.setLoop(true);
	this->bgMusic.play();

	this->clickSound_Buffer.loadFromFile("Sounds/click.wav");

	this->clickSound.setBuffer(this->clickSound_Buffer);
}

//Initialize Fonts
void Game::initFonts()
{
	this->font.loadFromFile("Fonts/Plaguard.otf");
}

//Initialize Texts and set Fonts
void Game::initTexts()
{
	this->textStart.setString("START");
	this->textStart.setFont(this->font);
	this->textStart.setCharacterSize(25);
	this->textStart.setPosition(sf::Vector2f(static_cast<float>(this->windowSize.x) /2-50,
		static_cast<float>((this->windowSize.y)/2-50)));

	this->textCredit.setString("CREDIT");
	this->textCredit.setFont(this->font);
	this->textCredit.setCharacterSize(25);
	this->textCredit.setPosition(sf::Vector2f(static_cast<float>(this->windowSize.x) / 2 - 50,
		static_cast<float>((this->windowSize.y) / 2 - 25)));

	this->textExit.setString("EXIT");
	this->textExit.setFont(this->font);
	this->textExit.setCharacterSize(25);
	this->textExit.setPosition(sf::Vector2f(static_cast<float>(this->windowSize.x) / 2 - 50,
		static_cast<float>((this->windowSize.y) / 2 )));

	this->textCreditinfo.setString("This Game was made solely by\nFANGJANG LIMBU");
	this->textCreditinfo.setFont(this->font);
	this->textCreditinfo.setCharacterSize(25);
	this->textCreditinfo.setPosition(sf::Vector2f(static_cast<float>(this->windowSize.x) / 2 - 160,
		static_cast<float>((this->windowSize.y) / 2 - 80)));

	this->textHighScore.setFont(this->font);
	this->textHighScore.setCharacterSize(25);
	this->textHighScore.setPosition(sf::Vector2f(static_cast<float>(this->windowSize.x) / 2 + 200,
		20.f));

	this->textPoints.setFont(this->font);
	this->textPoints.setCharacterSize(25);
	this->textPoints.setPosition(sf::Vector2f(this->textHighScore.getPosition().x,
		this->textHighScore.getPosition().y + 30));

	this->textGameOver.setString("GAME OVER\nPRESS ENTER TO PLAY AGAIN");
	this->textGameOver.setFont(this->font);
	this->textGameOver.setFillColor(sf::Color::Red); 
	this->textGameOver.setCharacterSize(40);
	this->textGameOver.setPosition(sf::Vector2f((this->windowSize.x / 2) - 200,
		(this->windowSize.y / 2) - 100));
}

//Check and Store highscore in memory
void Game::checkHighScore()
{
	int storePoints = 0;
	file = fopen("Data.dat", "r");
	if (file == NULL)
	{
		file = fopen("Data.dat", "w");
	}
	else
		(void)fscanf(file, "%d", &storePoints);
	std::stringstream textScore;
	textScore << "HIGH SCORE :" << storePoints;
	this->textHighScore.setString(textScore.str());
}

//Public Functions
// 
//Constructor
Game::Game()
{
	this->initWindow();
	this->checkHighScore();
	this->initSprites();
	this->initTextures();
	this->initSounds();
	this->initFonts();
	this->initTexts();
}

//Desturctor
Game::~Game()
{
	delete this->window;
}

//Running State Checker
const bool Game::running() const
{
	return this->window->isOpen();
}

//Main menu state checker
const bool Game::checkMenu() const
{
	return menuState;
}

//Credit State checker
const bool Game::checkCredit() const
{
	return creditState;
}

//Poll Events
void Game::pollEvents()
{
	//Events regarding Closing window
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (this->menuState == true)
			{
				this->window->close();
			}
		}
	}

	//Selecting the menu options
	if (this->menuState == true && this->creditState == false)
	{
		if (sf::Keyboard::isKeyPressed(::sf::Keyboard::Up))
		{
			if (arrowClick == false)
			{
				arrowClick = true;
				switch (options)
				{
				case Game::menuOptions::start:
					options = Game::menuOptions::exit;
					break;
				case Game::menuOptions::credit:
					options = Game::menuOptions::start;
					break;
				case Game::menuOptions::exit:
					options = Game::menuOptions::credit;
					break;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (arrowClick == false)
			{
				arrowClick = true;
				switch (options)
				{
				case Game::menuOptions::start:
					options = Game::menuOptions::credit;
					break;
				case Game::menuOptions::credit:
					options = Game::menuOptions::exit;
					break;
				case Game::menuOptions::exit:
					options = Game::menuOptions::start;
					break;
				}
			}
		}
		else
			arrowClick = false;
	}

	//Taking Enter input 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (enterClick == false)
		{
			enterClick = true;
			if (this->creditState == false && this->menuState == true)
			{
				switch (options)
				{
				case Game::menuOptions::start:
					this->clickSound.play();
					this->menuState = false;
					break;
				case Game::menuOptions::credit:
					this->clickSound.play();
					creditState = true;
					break;
				case Game::menuOptions::exit:
					this->window->close();
					break;
				}
			}
			else if (creditState == true)
			{
				this->clickSound.play();
				creditState = false;
			}
		}
	}
	else
		enterClick = false;

	//Exiting Credit State
}

//Render Objects of Main menu
void Game::renderMenu()
{
	switch (options)
	{
		case menuOptions::start:
			this->textStart.setFillColor(sf::Color::Blue);
			this->textCredit.setFillColor(sf::Color::White);
			this->textExit.setFillColor(sf::Color::White);
			break;
		case menuOptions::credit:
			this->textCredit.setFillColor(sf::Color::Blue);
			this->textStart.setFillColor(sf::Color::White);
			this->textExit.setFillColor(sf::Color::White);
			break;
		case menuOptions::exit:
			this->textExit.setFillColor(sf::Color::Blue);
			this->textStart.setFillColor(sf::Color::White);
			this->textCredit.setFillColor(sf::Color::White);
	}
	if (this->creditState == false && this->menuState == true)
	{
		this->window->draw(this->textStart);
		this->window->draw(this->textCredit);
		this->window->draw(this->textExit);
	}
}

//Render Objects of Credit
void Game::renderCredit()
{
	this->window->draw(this->textCreditinfo);
}

//Render Objects of Game
void Game::renderGame()
{

}

//Draw complementary objects
void Game::drawWindow()
{
	this->window->clear();
	this->window->draw(this->bg);
	this->window->draw(this->bird);
}

//Dsipaly all Drawn Objects
void Game::display()
{
	this->window->draw(this->textHighScore);
	if (this->gameOver)
	{
		this->window->draw(this->textGameOver);
	}
	this->window->display();
}

void Game::gameUpdate()
{
	//Resetting variables for new game
	if (this->newGame)
	{
		this->newGame = false;
		this->gameOver = false;
		this->jumpState = false;
		this->points = 00;
		this->bird.setPosition(sf::Vector2f(50.f, (this->windowSize.y) / 2 - 120));
		this->bird.setRotation(0.f);

		this->wallsDown.clear();
		this->wallsup.clear();

		//Spawing the first lower Wall with random Height
		this->wallsDown.push_back(this->wall);
		this->wallsDown[this->wallsDown.size() - 1].setPosition(sf::Vector2f(this->wall.getPosition().x,
			rand() % (450 - 200) + 200));

		//Spawing the first upper wall respestive to the first lower wall
		this->wallsup.push_back(this->wallMirror);
		this->wallsup[this->wallsup.size() - 1].setPosition(sf::Vector2f(this->wall.getPosition().x,
			this->wallsDown[this->wallsDown.size() - 1].getPosition().y - 150));
	}

	//If the game is not over, the gameplay starts or continues
	if (!(this->gameOver))
	{
		this->gamePlay();
	}
	else if (this->gameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			this->newGame = true;
		}
	}

	//Drawing the walls
	//Down walls
	for (auto& i : this->wallsDown)
	{
		this->window->draw(i);
	}
	//Upper walls
	for (auto& i : this->wallsup)
	{
		this->window->draw(i);
	}

	//Checking and Printing the points
	std::stringstream pts;
	pts << "SCORE : " << this->points;
	this->textPoints.setString(pts.str());
	this->window->draw(this->textPoints);
}

void Game::gamePlay()
{
	//Spawning the walls in distance
	if (this->wallsDown[this->wallsDown.size() - 1].getPosition().x + 400 <
		this->window->getSize().x)
	{
		this->wallsDown.push_back(this->wall);
		this->wallsDown[this->wallsDown.size() - 1].setPosition(sf::Vector2f(this->wall.getPosition().x,
			rand() % (450 - 200) + 200));

		this->wallsup.push_back(this->wallMirror);
		this->wallsup[this->wallsup.size() - 1].setPosition(this->wall.getPosition().x,
			this->wallsDown[this->wallsDown.size() - 1].getPosition().y - 150);
	}

	//Moving and erasing the walls
	//Down walls
	for (int i = 0; i < this->wallsDown.size(); i++)
	{
		//Moving the walls
		this->wallsDown[i].move(-2.75f, 0.f);
		this->wallsup[i].move(-2.75f, 0.f);

		//Erasing out of Screen Walls
		if (this->wallsDown[i].getPosition().x + 100 < 0)
		{
			this->wallsup.erase(this->wallsup.begin() + i);
			this->wallsDown.erase(this->wallsDown.begin() + i);
		}
	}

	//Implementing gravity
	if (this->jumpState == false && this->bird.getPosition().y < this->window->getSize().y)
	{
		this->gravityVelocity += this->gravity;
		this->bird.move(this->gravity);
		this->bird.setRotation(20.f);
	}

	//Checking if the space key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!(this->spaceClick))
		{
			this->spaceClick = true;
			if (!(this->jumpState))
			{
				this->jumpState = true;
				this->initJumpPos = this->bird.getPosition().y;
			}
		}
	}
	else
		this->spaceClick = false;

	//Implementing the jump
	if (this->jumpState)
	{
		if (this->bird.getPosition().y > (this->initJumpPos - this->jumpHeight))
		{
			this->bird.setRotation(-20.f);
			this->bird.move(this->jumpSpeed);
		}
		else
		{
			this->jumpState = false;
		}
	}

	if ((this->wallsDown.front().getPosition().x + 100) < this->bird.getPosition().x - (this->bird.getSize().x / 2))
	{
		this->points++;
	}

	/*Checking if a wall is crossed
	for (auto& i : this->wallsDown)
	{
		if ((i.getPosition().x + 100) < ((this->bird.getPosition().x - (this->bird.getSize().x / 2))))
		{
			this->points++;
		}
	}
	*/

	if (this->bird.getPosition().y == this->windowSize.y )
	{
		this->gameOver = true;
	}
}
