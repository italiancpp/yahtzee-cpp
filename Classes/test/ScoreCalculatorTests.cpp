#include "gtest/gtest.h"
#include "../Yahtzee/ScoreCalculator.h"
#include "../Yahtzee/YahtzeeWriter.h"
#include <vector>

class FakeWriter : public YahtzeeWriter
{
	virtual void startTurnFor( size_t player_count, size_t current_turn, size_t const turns_number ) 
	{
	}

	virtual void showPotentialScores( ScoreTable scores ) 
	{
	}

	virtual void newGameCreated( const std::vector<DicePlayer>& players, size_t totalTurns ) 
	{
	}

	virtual void _startTurnFor( DicePlayer& player, size_t currentTurn ) 
	{
	}

	virtual void diceRolled( DicePlayer& player, const std::vector<Die>& dice, size_t currentShot, const ScoreTable& scores ) 
	{
	}

	virtual void diceRolledNoMoreShots( DicePlayer& player, const std::vector<Die>& dice, size_t currentShot, const ScoreTable& scores ) 
	{
	}

	virtual void endTurnFor( DicePlayer& player, const ScoreTable& currentScores, size_t justEndedTurn ) 
	{
	}

};

using namespace std;

TEST(ScoreCalculatorTests, on_pair)
{
	FakeWriter writer;
	ScoreCalculator calculator(writer, 6);
	int diceArr[] = {1,1,3,4,5};
	vector<Die> dice(diceArr, diceArr+5);
	
	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	ScoreTable actualTable;
	calculator.CheckScore(dice, true, actualTable);

	ASSERT_EQ(actualTable, expectedTable);
}