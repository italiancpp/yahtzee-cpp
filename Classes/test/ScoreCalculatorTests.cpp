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

class ScoreCalculatorTests : public testing::Test
{
public:
	ScoreCalculatorTests()
		: calculator(writer, 6), dice(5, Die(1))
	{

	}

protected:
	void CheckScoreOnFirstShot(const ScoreTable& expected);
	void CheckScoreOnShotDifferentFromFirst(const ScoreTable& expectedTable);
	
	FakeWriter writer;
	ScoreCalculator calculator;
	vector<Die> dice;
};

void ScoreCalculatorTests::CheckScoreOnFirstShot(const ScoreTable& expectedTable)
{
	ScoreTable actualTable;
	calculator.CheckScore(dice, true, actualTable);
	ASSERT_EQ(actualTable, expectedTable);
}

void ScoreCalculatorTests::CheckScoreOnShotDifferentFromFirst(const ScoreTable& expectedTable)
{
	ScoreTable actualTable;
	calculator.CheckScore(dice, false, actualTable);
	ASSERT_EQ(actualTable, expectedTable);
}

TEST_F(ScoreCalculatorTests, on_pair)
{
	int diceArr[] = {1,1,3,4,5};
	dice.assign(diceArr, diceArr+5);
	
	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	CheckScoreOnFirstShot(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_tris)
{
	int diceArr[] = {1,1,1,4,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	CheckScoreOnFirstShot(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_double_pair)
{
	int diceArr[] = {1,1,3,3,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 6);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	CheckScoreOnFirstShot(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_straight)
{
	int diceArr[] = {1,2,3,4,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 1);
	expectedTable.AssignScoreIfNotAssigned(Scores::two, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);
	expectedTable.AssignScoreIfNotAssigned(Scores::straight, 25);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::straight, 20);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_full)
{
	int diceArr[] = {1,1,3,3,3};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 9);
	expectedTable.AssignScoreIfNotAssigned(Scores::full, 35);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::full, 30);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_poker)
{
	int diceArr[] = {1,1,1,1,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);
	expectedTable.AssignScoreIfNotAssigned(Scores::poker, 45);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::poker, 40);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_generala)
{
	int diceArr[] = {1,1,1,1,1};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 5);
	expectedTable.AssignScoreIfNotAssigned(Scores::generala, 55);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::generala, 50);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}