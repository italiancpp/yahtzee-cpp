#include "gtest/gtest.h"
#include "../Yahtzee/DiceRoller.h"
#include "../Yahtzee/Generala.h"
#include "../Yahtzee/GameConfiguration.h"
#include "../Yahtzee/Yahtzee.h"

class MockYahtzeeWriter : public YahtzeeWriter
{
public:
	MockYahtzeeWriter()
		:	called_newGameCreated(0), called_startTurnFor(0),
			called_diceRolled(0), called_scoreCalculated(0), called_endTurnFor(0),
			called_gameOver(0)
	{

	}

	virtual void startTurnFor(size_t player_count, size_t current_turn, size_t const turns_number);

	virtual void newGameCreated( const std::vector<DicePlayer>& pPlayers, size_t pTotalTurns ) 
	{
		++called_newGameCreated;
		newGameCreated_numOfPlayers = pPlayers.size();
		players = pPlayers;
		totalTurns = pTotalTurns;
	}

	virtual void _startTurnFor( DicePlayer& player, size_t currentTurn ) 
	{
		++called_startTurnFor;
		startTurnFor_current_turn_arg = currentTurn;
		startTurnFor_playerName = player.name;
	}

	virtual void diceRolled( const std::vector<Die>& dice, size_t currentShot, size_t remainingShots ) 
	{
		++called_diceRolled;
		diceRolled_diceValue = dice;
		diceRolled_currentShot = currentShot;
		diceRolled_remaningShots = remainingShots;
	}

	virtual void endTurnFor( DicePlayer& player, const ScoreTable& currentScores, size_t justEndedTurn ) 
	{
		++called_endTurnFor;
		endTurnFor_playerName = player.name;
		endTurnFor_currentScores = currentScores;
	}

	virtual void scoreCalculated( const ScoreTable& scores ) 
	{
		++called_scoreCalculated;	
		scoreCalculated_scores = scores;
	}

	virtual void gameOver() 
	{
		++called_gameOver;
	}

	ScoreTable lastPotentialScore;
	ScoreTable _showPotentialScoresArgs;

	// new stuff
	std::vector<DicePlayer> players;
	size_t totalTurns;

	// function called info
	int called_newGameCreated;
	int called_startTurnFor;
	int called_diceRolled;
	int called_scoreCalculated;
	int called_endTurnFor;
	int called_gameOver;

	// functiona called args
	size_t newGameCreated_numOfPlayers;
	size_t startTurnFor_current_turn_arg;
	std::string startTurnFor_playerName;
	std::vector<Die> diceRolled_diceValue;
	size_t diceRolled_remaningShots;
	size_t diceRolled_currentShot;
	ScoreTable scoreCalculated_scores;
	std::string endTurnFor_playerName;
	ScoreTable endTurnFor_currentScores;
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

	void AssignDiceValues(int values[5])
	{
		for (int i=0; i<5; i++)
		{
			mockedValues[i] = values[i];
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
	YahtzeeTest()
		: _configuration(CreateDefaultGameConfiguration())
	{

	}

	virtual void SetUp()
	{
		_game.reset(new Generala(_roller, _configuration, &_writer));
	}

	virtual void TearDown()
	{
	}

	GameConfiguration _configuration;
	MockDiceRoller _roller;
	std::unique_ptr<Generala> _game;
	MockYahtzeeWriter _writer;
};

TEST_F(YahtzeeTest, empty_game_should_have_no_players)
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

//////////////////////////////////////////////////////////////////////////

/* TO-DO

 - refactoring dei test --> fixture
 - throw exception (o altro) se fai un SelectScore su una ScoreName già assegnata
 - più test di gioco
*/

using namespace std;

TEST(NewYahtzeeTest, on_creation_should_do_nothing)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	DicePlayer player1("Marco", GameConfiguration::DEFAULT_DICE_ROLLER);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);

	ASSERT_EQ( writer.called_newGameCreated, 0 );
}

TEST(NewYahtzeeTest, on_new_game_should_notify_writer)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	DicePlayer player1("Marco", GameConfiguration::DEFAULT_DICE_ROLLER);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);
	game.newGame();

	ASSERT_EQ( writer.called_newGameCreated, 1 );
	ASSERT_EQ( writer.newGameCreated_numOfPlayers, 1 );
}

TEST(NewYahtzeeTest, on_start_turn_should_notify_writer_with_first_player)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	DicePlayer player1("Marco", GameConfiguration::DEFAULT_DICE_ROLLER);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);
	game.newGame();

	ASSERT_EQ( writer.called_startTurnFor, 1 );
	ASSERT_EQ( writer.startTurnFor_current_turn_arg , 1u );
	ASSERT_STRCASEEQ( writer.startTurnFor_playerName.c_str(), "Marco" );
}

TEST(NewYahtzeeTest, on_roll_dice_should_notify_writer_and_calculate_score)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	MockDiceRoller mockedRoller;
	int mockedDiceValueArr[5] = {1,1,2,3,4};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	vector<Die> mockedDiceValue(mockedDiceValueArr, mockedDiceValueArr + 5);

	ScoreTable mockedScores;
	mockedScores.AssignScoreIfNotAssigned(Scores::one, 2, false);
	mockedScores.AssignScoreIfNotAssigned(Scores::two, 2, false);
	mockedScores.AssignScoreIfNotAssigned(Scores::three, 3, false);
	mockedScores.AssignScoreIfNotAssigned(Scores::four, 4, false);

	DicePlayer player1("Marco", mockedRoller);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);
	game.newGame();
	game.rollDice();

	ASSERT_EQ( writer.called_diceRolled, 1 );
	ASSERT_EQ( writer.diceRolled_currentShot , 1u );
	ASSERT_EQ( writer.diceRolled_diceValue , mockedDiceValue );
	ASSERT_EQ( writer.diceRolled_remaningShots, 2);
	ASSERT_EQ( writer.called_scoreCalculated, 1);
	ASSERT_EQ( writer.scoreCalculated_scores, mockedScores );
}

TEST(NewYahtzeeTest, on_roll_dice_three_times_should_remain_no_shots)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	MockDiceRoller mockedRoller;
	int mockedDiceValueArr[5] = {1,1,2,3,4};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	vector<Die> mockedDiceValue(mockedDiceValueArr, mockedDiceValueArr + 5);

	DicePlayer player1("Marco", mockedRoller);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);
	game.newGame();
	game.rollDice();
	game.rollDice();
	game.rollDice();

	// e se tiriamo più di tre volte???

	ASSERT_EQ( writer.called_diceRolled, 3 );
	ASSERT_EQ( writer.diceRolled_currentShot , 3u );
	ASSERT_EQ( writer.diceRolled_remaningShots, 0u);
	ASSERT_EQ( writer.called_scoreCalculated, 3);
}

TEST(NewYahtzeeTest, on_select_score_should_assign_scores_to_current_player)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	MockDiceRoller mockedRoller;
	int mockedDiceValueArr[5] = {1,1,1,1,1};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	vector<Die> mockedDiceValue(mockedDiceValueArr, mockedDiceValueArr + 5);
	ScoreTable expectedSelectedScores;
	expectedSelectedScores.AssignScoreIfNotAssigned(Scores::generala, 55, true);

	DicePlayer player1("Marco", mockedRoller);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);
	game.newGame();
	game.rollDice();
	game.SelectScore(Scores::generala);

	ASSERT_EQ(writer.endTurnFor_currentScores, expectedSelectedScores);
}

TEST(NewYahtzeeTest, on_select_score_should_end_turn_for_current_player)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	MockDiceRoller mockedRoller;
	int mockedDiceValueArr[5] = {1,1,1,1,1};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	vector<Die> mockedDiceValue(mockedDiceValueArr, mockedDiceValueArr + 5);

	DicePlayer player1("Marco", mockedRoller);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), defaultConfig, writer);
	game.newGame();
	game.rollDice();
	game.SelectScore(Scores::generala);

	ASSERT_EQ( writer.called_endTurnFor, 1 );
	ASSERT_STRCASEEQ( writer.endTurnFor_playerName.c_str(), "Marco" );
}

TEST(NewYahtzeeTest, on_select_score_should_start_turn_for_other_player)
{
	auto defaultConfig = CreateDefaultGameConfiguration();
	MockDiceRoller mockedRoller;
	int mockedDiceValueArr[5] = {1,1,1,1,1};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	vector<Die> mockedDiceValue(mockedDiceValueArr, mockedDiceValueArr + 5);

	DicePlayer player1("Marco", mockedRoller);
	DicePlayer player2("Gianluca", mockedRoller);
	vector<DicePlayer> players; 
	players.push_back(player1); 
	players.push_back(player2); 
	MockYahtzeeWriter writer;
	Yahtzee game(players, defaultConfig, writer);
	game.newGame();
	game.rollDice();
	game.SelectScore(Scores::generala);

	ASSERT_EQ( writer.called_startTurnFor, 2 );
	ASSERT_EQ( writer.startTurnFor_playerName, "Gianluca" );
}

TEST(NewYahtzeeTest, on_select_score_with_only_one_turn_should_call_game_over)
{
	GameConfiguration oneTurnConfig(5, 6, 1);

	DicePlayer player1("Marco", GameConfiguration::DEFAULT_DICE_ROLLER);
	MockYahtzeeWriter writer;
	Yahtzee game(vector<DicePlayer>(1, player1), oneTurnConfig, writer);
	game.newGame();
	game.rollDice();
	game.SelectScore(Scores::generala);

	ASSERT_EQ( writer.called_gameOver, 1 );
}