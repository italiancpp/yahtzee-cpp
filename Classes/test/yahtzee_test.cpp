#include "gtest/gtest.h"

#include "../Yahtzee/Generala.h"

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
	Generala _game;
};

TEST_F(YahtzeeTest, DefaultConstructor)
{
	EXPECT_EQ(0u, _game.playerNumber());
}

TEST_F(YahtzeeTest, SetNumberOfPlayerNumber)
{
	auto playerNumber = 2u;
	_game.playerNumber(playerNumber);

	EXPECT_EQ(playerNumber, _game.playerNumber());
}

// TEST_F(YahtzeeTest, Dequeue)
// {
// }

// TEST_F(YahtzeeTest, Map)
// {
// }
