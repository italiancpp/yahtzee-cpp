#pragma once
#include "DicePlayer.h"

class YahtzeeWriter
{
public:
	virtual void startTurnFor(size_t player_count, size_t current_turn, size_t const turns_number) = 0;
	virtual void showPotentialScores(ScoreTable scores) = 0;

	void numberOfPlayersChanged(size_t oldValue, size_t newValue); // non ha senso perché il numero di giocatore dipenderà dalla config e sarà fisso da gioco a gioco
	void writeLine(std::string s)
	{

	}

	//
	virtual void newGameCreated(const std::vector<DicePlayer>& players, size_t totalTurns) = 0;
	virtual void _startTurnFor(DicePlayer& player, size_t currentTurn) = 0;
	void diceRolled(DicePlayer& player, const std::vector<int>& dice, size_t currentShot); // e.g. mostra il valore dei dadi
	void _showPotentialScores(DicePlayer& player, const ScoreTable& scores); // e.g. mostra le score che hai fatto (comprese le attuali)
	void endTurnFor(DicePlayer& player, const ScoreTable& currentScores, size_t justEndedTurn);
	void gameOver();

};