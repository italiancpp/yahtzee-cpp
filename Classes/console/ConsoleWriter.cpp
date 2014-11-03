#include <ostream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
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
	cout << "*************************************" << endl;
	cout << "* Score                             *" << endl;
	cout << "*************************************" << endl;
	cout << scores << endl;
	cout << endl;
}

// TODO current shot e ramainign sono girati!!!
void ConsoleWriter::diceRolled(const std::vector<Die> &dice, size_t currentShot, size_t remainingShots)
{
	cout << "*************************************" << endl;
	cout << "* Dadi                              *" << endl;
	cout << "*************************************" << endl;
	cout << "Tiro numero: " << currentShot << " su " << remainingShots << endl;
	cout << "Valore:    ";
	for_each(begin(dice), end(dice), [](const Die die) {
		cout << die.value << " ";
	});
	cout << endl;
	cout << "           ";
	for_each(begin(dice), end(dice), [](const Die die) {
		cout << (die.hold? " " : "^") << " ";
	});
	cout << endl;
	cout << "Posizione: ";
	for(int i = 0; i < dice.size(); i++)
	{
		cout << i+1 << " ";
	}
	cout << endl;
	cout << endl;
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


/*
     1 1 2 3 5   remaning: 2
       ^ ^ ^
pos: 1 2 3 4 5

[1] one -> 0 *
[2] ...
...

hold (h) or served (s)? s
which line (only with *): 1

Player Marco, end of turn 2

[1] one ->
[2] ...

...> premere un tasto


hold (h) or served (s)? h
which dice to hold? 1 3

     1 1 2 3 5   remaning: 1
       ^   ^ ^
pos: 1 2 3 4 5
 */

void ConsoleWriter::run()
{
	auto playerNumber = getPlayerNumber();
	auto players = createPlayers(playerNumber);

	GameConfiguration yahtzeeConfig(5, 6, 13);
	Yahtzee yahtzee(players, yahtzeeConfig, *this);

	yahtzee.newGame();
	while(true)
	{
		yahtzee.rollDice();

		cout << "Cosa vuoi fare? premi S ed invio per selezionare lo score oppure premi h e invio per selezionare quali dati tenere ";

		string cmd;
		cin >> cmd;

		if (cmd == "s")
		{
			selectScore(yahtzee);
		}
		if (cmd == "h")
		{
			selectDieToHold(yahtzee);
		}
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

void ConsoleWriter::selectScore(Yahtzee &yahtzee)
{
	cout << "Scrivi la posizione dello score da tenere (1, 2, etc ..) ";
	int scoreIndex;
	cin >> scoreIndex;
	yahtzee.selectScore((Scores::ScoreName)(scoreIndex - 1));
}


template<typename T>
ostream& operator<<(ostream& stream, const vector<T> &values)
{
	for_each(values.begin(), values.end(), [&](const T &v) {
		stream << v << " ";
	});
	return stream;
//	for (int i=0; i<table.scores.size(); ++i)
//		stream << score_names[i] << " -> " << table.scores[i].value << (table.scores[i].assigned ? "" : " *") << std::endl;
//	return stream;
}

void ConsoleWriter::selectDieToHold(Yahtzee &yahtzee)
{

	cin.ignore();
	cout << "Scrivi la posizione del datoda tenere (1 2 etc ...) ";
	string dieIndex;
	getline(cin, dieIndex);

	vector<string> tokens;
	istringstream iss(dieIndex);
//	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
	istream_iterator<string> eos;
	for(istream_iterator<string> iit(iss); iit != eos; ++iit)
	{
		tokens.push_back(*iit);
	}

	std::vector<int> diceToHold;
	for (auto& token : tokens)
	{
		auto h = stoul(token);
		if (h < 6)
		{
			diceToHold.push_back(h - 1);
		}
	}

	// TODO holdDice è 0 based per cui quì ci potrebbe essereun bug test rosso?
	yahtzee.holdDice(diceToHold);
}


