#include "Yahtzee.h"
#include "YahtzeeWriter.h"
#include "GameConfiguration.h"

Yahtzee::Yahtzee( const std::vector<DicePlayer>& _players, const GameConfiguration& _conf, YahtzeeWriter& _writer )
	:	players(_players), playerStates(_players.size()), 
		configuration(_conf), writer(_writer),
		currentPlayerIndex(0u), currentTurnNumber(0u)
{

}
using namespace std;
void Yahtzee::newGame()
{
	writer.newGameCreated(players, configuration.TurnsNumber);
	currentTurnNumber = 1u;
}

void Yahtzee::startTurn()
{
	writer._startTurnFor(players[currentPlayerIndex], currentTurnNumber);
}

void Yahtzee::rollDice()
{

}

void Yahtzee::holdDice( const std::vector<int>& diceToHold )
{

}

void Yahtzee::endTurn( Scores::ScoreName score )
{

}

std::string Yahtzee::getWinner()
{
	return "";
}

size_t Yahtzee::numberOfPlayers() const
{
	return players.size();
}
