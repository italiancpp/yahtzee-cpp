#include <ostream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "ConsoleWriter.h"
#include "../Yahtzee/Yahtzee.h"
#include "../Yahtzee/GameConfiguration.h"

using namespace std;

ConsoleWriter::ConsoleWriter()
{

}

ConsoleWriter::~ConsoleWriter()
{

}

void ConsoleWriter::startTurnFor(DicePlayer &player, size_t currentTurn)
{
	cout << "Inizia il turno (" << currentTurn << ") per il giocatore '" << player.Name() << "'" << endl;
}

void ConsoleWriter::newGameCreated(const std::vector<DicePlayer> &players, size_t totalTurns)
{
	cout << "Inizio GAME!!!" << endl;
}

void ConsoleWriter::scoreCalculated(const ScoreTable &scores)
{
	cout << "Score:" << scores << endl;
}

void ConsoleWriter::diceRolled(const std::vector<Die> &dice, size_t currentShot, size_t remainingShots)
{
	cout << "Tiro numero: " << currentShot << " su " << remainingShots << endl;
	for_each(begin(dice), end(dice), [](const Die die) {
		cout << die.value << (die.hold? "*" : "") << endl;
	});
}

void ConsoleWriter::endTurnFor(DicePlayer &player, const ScoreTable &currentScores, size_t justEndedTurn)
{
	cout << "Fine del turno per " << player.Name() << endl;
	cout << "Punteggio " << currentScores << endl;
	cout << "Turni terminati " << justEndedTurn << endl;
}

void ConsoleWriter::gameOver()
{
	cout << "GAME OVER!!!!!" << endl;
}

void ConsoleWriter::run()
{
	auto playerNumber = getPlayerNumber();
	auto players = createPlayers(playerNumber);

	GameConfiguration yahtzeeConfig(5, 6, 13);
	Yahtzee yahtzee(players, yahtzeeConfig, *this);

	yahtzee.newGame();
	while(true)
	{
		cout << "Ecco il tuo tiro" << endl;
		yahtzee.rollDice();

		cout << "Cosa vuoi fare? premi S ed invio per selezionare lo score oppure scrivi" << endl;

	}
}





// TODO - Controllare che inseirscano almeno 1 giocatore
int ConsoleWriter::getPlayerNumber()
{
	int playerNumber = 0;
	cout << "Quanti giocatori vogliono giocare? ";
	cin >> playerNumber;
	return playerNumber;
}

std::vector<DicePlayer> ConsoleWriter::createPlayers(int number)
{
	std::vector<DicePlayer> players;
	for (int i = 0; i < number; ++i)
	{
		std::stringstream ss;
		ss << "Player" << number;
		auto player = DicePlayer(ss.str(), GameConfiguration::DEFAULT_DICE_ROLLER);
		players.push_back(player);
	}

	return players;

}
