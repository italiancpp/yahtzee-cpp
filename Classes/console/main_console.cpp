#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "../Yahtzee/Yahtzee.h"
#include "../Yahtzee/GameConfiguration.h"
#include "../Yahtzee/YahtzeeWriter.h"
#include "ConsoleWriter.h"


class InputConsole
{
	Yahtzee &_yahtzee;

public:
	InputConsole(Yahtzee &yahtzee)
		:_yahtzee(yahtzee)
	{
	}

	void Run()
	{
		std::string line;
		getline(std::cin, line);
	}
};

int main(int argc, char **argv)
{
//	const std::vector<DicePlayer> players = {
//		DicePlayer("P1", GameConfiguration::DEFAULT_DICE_ROLLER),
//		DicePlayer("P2", GameConfiguration::DEFAULT_DICE_ROLLER)
//	};
//
//	GameConfiguration yahtzeeConfig(5, 6, 13);
//	ConsoleWriter consoleWriter;
//	Yahtzee yahtzee(players, yahtzeeConfig, consoleWriter);
//
//
//	InputConsole inputConsole(yahtzee);
//	inputConsole.Run();

	ConsoleWriter consoleYahtzee;

	consoleYahtzee.run();



	return 0;
}
