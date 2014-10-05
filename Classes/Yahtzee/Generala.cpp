#include "Generala.h"
#include "DiceRoller.h"
#include "ScoreValues.h"
#include "ScoreCalculator.h"
//#include "RuleGenerator.h" // INVECCHIAMENTO
#include "GameState.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void hold_all(vector<Die>& dice, bool hold)
{
	for (auto& die : dice)
	{
		die.hold = hold;
	}
}

void print_dice(const vector<Die>& dice)
{
	for (auto& die : dice)
	{
		cout << die.value << " ";
	}
	cout << endl;
	cout << endl;
}

void ChooseScore(GameState& state)
{
	cout << "Choose a line with '*' > ";
	string line;
	getline(cin, line);
	cout << "CHOSEN " << line << endl;
	
	state.AssignScoreFromPotential(line);
	
	cout << endl;
	cout << "CURRENT SCORES" << endl;
	cout << state.currentScores;
} 

static const size_t dice_number = 5;
static const unsigned short max_dice_value = 6;
static const size_t turns_number = Scores::scores_count;
static const size_t shots_number = 3;

int Generala::Start()
{
	vector<Die> dice(dice_number, Die(1));
	DiceRoller roller(max_dice_value);
	//ScoreCalculator calculator(RuleGenerator::GenerateRules());
	ScoreCalculator calculator;

	// size_t playerNum = 1u;
	cout << "Generala Game (alpha version)" << endl;
	cout << endl;
	cout << "Note: input errors are not checked" << endl;
	cout << endl;


	// cout << "How many players? > ";
	// cin >> playerNum;	
	// vector<GameState> states(playerNum);
	// cout << endl;
	// cout << "Created game for " << playerNum << " players!" << endl;
	// cin.ignore();
	// system("cls");

	size_t current_turn = turns_number;

	while (current_turn--)
	{
		size_t player_count = 1u;
		for (auto& state : _states)
		{
			state.NewTurn();
		
			system("cls");
			cout << "Player [" << player_count++ << "] Turn: " << turns_number - current_turn << " of " << turns_number << endl;
			cout << endl;

			size_t current_shot = shots_number;

			while(current_shot--)
			{
				state.NewShot();

				roller.Roll(dice);
				print_dice(dice);
				
				calculator.CheckScore(dice, max_dice_value, state);
				cout << state.potentialScores;
				hold_all(dice, false);

				cout << endl;

				if (current_shot)
				{
					cout << "Hold? ('S' if served) > ";
					string toHold;
					getline( cin, toHold );

					if (toHold == "S" || toHold == "s")
					{
						ChooseScore(state);
						break;
					}

					else
					{
						istringstream ss(toHold);
						vector<string> tokens;
						copy(istream_iterator<string>(ss), istream_iterator<string>(), back_inserter(tokens));

						for (auto& token : tokens)
						{
							auto h = stoul(token);
							if (h < 6)
							{
								dice[h-1].hold = true;
							}
						}
					}
				}
				else 
				{
					ChooseScore(state);
				}
			}
		}
	}
		
	system("cls");

	size_t player_count = 1u;
	
	for (auto& state : _states)
	{
		cout << "-----" << endl;
		cout << "Player [" << player_count << "] FINAL SCORE TABLE" << endl;
		cout << endl;
		cout << state.currentScores << endl;
		cout << "Total Score: " << state.currentScores.TotalScore() << endl;
		cout << endl;
		player_count++;
	}
	
	cout << endl;
	auto worst_best = minmax_element(begin(_states), end(_states), [](const GameState& state1, const GameState& state2) 
		{
			return state1.currentScores.TotalScore() < state2.currentScores.TotalScore();
		});

	if (worst_best.first == worst_best.second)
	{
		cout << "Deuce!" << endl;
	}

	else if (_states.size() > 1)
	{
		cout << "The winner is player " << distance(begin(_states), worst_best.second) + 1 << endl;
		cout << "The worst is player " << distance(begin(_states), worst_best.first) + 1 << endl;
	}

	return 0;
}