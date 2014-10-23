#include "gtest/gtest.h"
#include "../Yahtzee/DiceRoller.h"
#include "../Yahtzee/Generala.h"
//#include <memory>

class MockYahtzeeWriter : public YahtzeeWriter
{
public:
	MockYahtzeeWriter()
		: _showPotentialScoresCalled(0)
	{

	}

	ScoreTable _showPotentialScoresArgs;
	int _showPotentialScoresCalled;


	virtual void startTurnFor(size_t player_count, size_t current_turn, size_t const turns_number);

	virtual void showPotentialScores(ScoreTable scores)
	{
		++_showPotentialScoresCalled;
		_showPotentialScoresArgs = scores;
	}

	ScoreTable lastPotentialScore;
};

class MockDiceRoller : public IDiceRoller
{
public:
	MockDiceRoller()
	{
		for (int i=0; i<5; i++)
		{
			mockedValues[i] = 1;
		}
	}

	void Roll(std::vector<Die>& dice) override
	{
		for (int i=0; i<5; i++)
		{
			dice[i] = mockedValues[i];
		}


	}

	int mockedValues[5];
};

class YahtzeeTest : public testing::Test
{
protected:
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	// virtual void SetUp() will be called before each test is run.  You
	// should define it if you need to initialize the varaibles.
	// Otherwise, this can be skipped.
	virtual void SetUp()
	{
		_game.reset(new Generala(_roller, &_writer));
	}

	// virtual void TearDown() will be called after each test is run.
	// You should define it if there is cleanup work to do.  Otherwise,
	// you don't have to provide it.
	//
	virtual void TearDown()
	{
	}

	// // A helper function that some test uses.
	// static int Double(int n)
	// {
	//  return 2 * n;
	// }

	// // A helper function for testing Queue::Map().
	// void MapTester(const Queue<int> *q)
	// {
	//  // Creates a new queue, where each element is twice as big as the
	//  // corresponding one in q.
	//  const Queue<int> *const new_q = q->Map(Double);

	//  // Verifies that the new queue has the same size as q.
	//  ASSERT_EQ(q->Size(), new_q->Size());

	//  // Verifies the relationship between the elements of the two queues.
	//  for ( const QueueNode<int> *n1 = q->Head(), * n2 = new_q->Head();
	//          n1 != NULL; n1 = n1->next(), n2 = n2->next() )
	//  {
	//      EXPECT_EQ(2 * n1->element(), n2->element());
	//  }

	//  delete new_q;
	// }

	// // Declares the variables your tests want to use.
	// Queue<int> q0_;
	// Queue<int> q1_;
	// Queue<int> q2_;

	MockDiceRoller _roller;
	std::unique_ptr<Generala> _game;
	MockYahtzeeWriter _writer;
};

TEST_F(YahtzeeTest, DefaultConstructor)
{
	EXPECT_EQ(0u, _game->playerNumber());
}

TEST_F(YahtzeeTest, show_play_name_after_set_number_of_Player)
{
	_game->playerNumber(2);
	//	_game->players({"p1", "p2"})

	//assert playerNumberOne

	EXPECT_EQ(2, _game->playerNumber());
}

TEST_F(YahtzeeTest, after_roll_dice_show_potential_score)
{
//	int tmp[] = {1, 2, 3, 4, 5};
	ScoreTable expected;
//	expected.TryAssignScore(Scores::straight, 260);
//	memcpy(&_roller.mockedValues, tmp, sizeof(tmp));
    _game->playerNumber(2u);

    _game->rollDice();

	EXPECT_TRUE(_writer._showPotentialScoresCalled > 0);
	EXPECT_EQ(expected, _writer._showPotentialScoresArgs);



}

TEST_F(YahtzeeTest, current_player_can_choose_score)
{
	int tmp[] = {1, 2, 3, 4, 5, 6};
	memcpy(&_roller.mockedValues, tmp, sizeof(tmp));
	_game->playerNumber(2u);

	_game->rollDice();

	_game->selectScore(Scores::ScoreName::straight);
}

TEST_F(YahtzeeTest, when_player_choose_score_the_turn_end)
{
	_game->playerNumber(2u);

	_game->rollDice();

	_game->selectScore(Scores::ScoreName::straight);

	//assert _writer->endTurn called
	//assert _writer->currentPlayerChanged called
}

TEST_F(YahtzeeTest, player_can_roll_at_max_three_times)
{
	_game->playerNumber(2u);

	_game->rollDice();
	_game->rollDice();
	_game->rollDice();

	auto potentialScore = _writer.lastPotentialScore;

	_game->rollDice();

//	EXPECT_EQ(potentialScore, _writer.lastPotentialScore);
	// assert _writer->

}

TEST_F(YahtzeeTest, frist_player_play_entire_turn)
{
	_game->playerNumber(2);

	_game->rollDice();
	int diceToHold[] = {1,3,5};
	std::vector<int> diceToHoldVec(diceToHold, diceToHold+3);
	_game->holdDice(diceToHoldVec);
	_game->rollDice();
	diceToHoldVec.resize(1);
	diceToHold[0] = 2;
	_game->holdDice(diceToHoldVec);
	_game->rollDice();
	_game->selectScore(Scores::ScoreName::full);

	//assert player NumberTwo

}


void MockYahtzeeWriter::startTurnFor(size_t player_count, size_t current_turn, size_t const turns_number)
{

}

