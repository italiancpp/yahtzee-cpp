#include "Yahtzee.h"
#include "YahtzeeWriter.h"
#include "GameConfiguration.h"

using namespace std;

Yahtzee::Yahtzee( const std::vector<DicePlayer>& _players, const GameConfiguration& _conf, YahtzeeWriter& _writer )
	:	players(_players), playerStates(_players.size()), 
		configuration(_conf), writer(_writer),
		currentPlayerIndex(0u), currentTurnNumber(0u),
		dice(_conf.NumberOfDice, 1), scoreCalculator(_writer, _conf.MaxDiceValue)
{

}

void Yahtzee::newGame()
{
	playerStates.clear(); playerStates.resize(players.size());
	currentTurnNumber = 1u;
	writer.newGameCreated(players, configuration.TurnsNumber);
}

void Yahtzee::startTurn()
{
	playerStates[currentPlayerIndex].NewTurn();
	writer._startTurnFor(players[currentPlayerIndex], currentTurnNumber);
}

void Yahtzee::rollDice()
{
	playerStates[currentPlayerIndex].NewShot();
	players[currentPlayerIndex].RollDice(dice);
	ScoreTable currentScore;
	scoreCalculator.CheckScore(dice, playerStates[currentPlayerIndex].IsFirstShot(), currentScore);
	
	if (players[currentPlayerIndex].MaxNumberOfShots() == playerStates[currentPlayerIndex].GetShotNumber())
	{
		writer.diceRolledNoMoreShots(players[currentPlayerIndex], dice, playerStates[currentPlayerIndex].GetShotNumber(), currentScore);
	}
	else
	{
		writer.diceRolled(players[currentPlayerIndex], dice, playerStates[currentPlayerIndex].GetShotNumber(), currentScore);
	}
}

void Yahtzee::holdDice( const std::vector<int>& diceToHold )
{
	for (int i=0; i<diceToHold.size(); ++i)
		dice[diceToHold[i]].hold = true;
}

void Yahtzee::endTurn( Scores::ScoreName score )
{
	ResetDice();
	size_t currPlayer = currentPlayerIndex;
	currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
	writer.endTurnFor(players[currPlayer], playerStates[currPlayer].currentScores, currentTurnNumber);
}

std::string Yahtzee::getWinner()
{
	return "";
}

size_t Yahtzee::numberOfPlayers() const
{
	return players.size();
}

void Yahtzee::ResetDice()
{
	for (int i=0; i<dice.size(); ++i)
		dice[i].hold = false;
}
