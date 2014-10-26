#pragma once
#include <string>
#include <vector>
#include "ScoreValues.h"
#include "DicePlayer.h"
#include "GameState.h"
#include "ScoreCalculator.h"

class GameConfiguration;
class YahtzeeWriter;

class Yahtzee
{
public:
	Yahtzee(const std::vector<DicePlayer>& _players, const GameConfiguration& _conf, YahtzeeWriter& _writer);

	void newGame(); // inizia il gioco (e.g. setta il primo turno)
	void startTurn(); // inizia il turno per il giocatore corrente
	void rollDice(); // tira i dadi per giocatore corrente e calcola il punteggio
	void holdDice(const std::vector<int>& diceToHold); // fa hold di alcuni dadi
	void endTurn(Scores::ScoreName score); // fine turno giocatore corrente
	std::string getWinner();

	size_t numberOfPlayers() const;

private:
	void ResetDice();

	std::vector<DicePlayer> players;
	std::vector<GameState> playerStates;
	const GameConfiguration& configuration;
	YahtzeeWriter& writer;
	ScoreCalculator scoreCalculator;

	// game-state info
	size_t currentPlayerIndex, currentTurnNumber;
	std::vector<Die> dice;
};