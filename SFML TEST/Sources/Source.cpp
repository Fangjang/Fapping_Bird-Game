#include"Game.h"

int main()
{
	//Creating Game class
	Game game;
	//Seeding the srand function with current time
	srand(time(NULL));

	//Main loop
	while (game.running())
	{
		game.drawWindow();
		if (game.checkMenu() == true)
		{
			if (!game.checkCredit())
			{
				game.renderMenu();
			}
			if(game.checkCredit())
			{
				game.renderCredit();
			}
		}
		else if (game.checkMenu() == false)
		{
			game.gameUpdate();
		}
		game.renderMenu();
		//Poll Events
		game.pollEvents();

		//Display all the Drawn objects
		game.display();
	}

	return 0;
}