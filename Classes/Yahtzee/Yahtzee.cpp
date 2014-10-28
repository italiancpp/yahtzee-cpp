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
	playerStates[currentPlayerIndex].NewTurn();
	writer._startTurnFor(players[currentPlayerIndex], currentTurnNumber);
}

GameState& Yahtzee::CurrentState()
{
	return playerStates[currentPlayerIndex];
}

void Yahtzee::rollDice()
{
	if (!CurrentPlayerHasMoreShots())
		throw exception("Current player does not have more shots");

	CurrentState().NewShot();
	players[currentPlayerIndex].RollDice(dice);
	scoreCalculator.CheckScore(dice, CurrentState().IsFirstShot(), CurrentState().potentialScores);
	writer.scoreCalculated(CurrentState().potentialScores);
	writer.diceRolled(dice, CurrentState().GetShotNumber(), players[currentPlayerIndex].MaxNumberOfShots() - CurrentState().GetShotNumber());
}

void Yahtzee::holdDice( const std::vector<int>& diceToHold )
{
	for (int i=0; i<diceToHold.size(); ++i)
		dice[diceToHold[i]].hold = true;
}

void Yahtzee::SelectScore( Scores::ScoreName score )
{
	size_t currPlayer = currentPlayerIndex;
	currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
	writer.endTurnFor(players[currPlayer], CurrentState().currentScores, currentTurnNumber);
	if (currentPlayerIndex == 0) // Verifico che il turno sia finito...
	{
		++currentTurnNumber;
		// verifico che il gioco sia finito
		if (currentTurnNumber > configuration.TurnsNumber) 
		{
			writer.gameOver();
			return;
		}
	}
	writer._startTurnFor(players[currentPlayerIndex], currentTurnNumber);
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

bool Yahtzee::CurrentPlayerHasMoreShots() const
{
	return players[currentPlayerIndex].MaxNumberOfShots() > playerStates[currentPlayerIndex].GetShotNumber();
}
