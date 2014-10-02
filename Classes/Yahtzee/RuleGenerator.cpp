#include "RuleGenerator.h"
#include <iostream>

using namespace std;

#define MAKE_RULE(...) [](const Histogram& histogram, GameState& state) \
	{ \
		__VA_ARGS__ \
	}

inline bool histogram_has(const Histogram& histogram, unsigned short val)
{
	return histogram.find(val) != end(histogram);
}

inline unsigned short Score(unsigned short score, const GameState& state, unsigned short extraIfFirstRoll = 5)
{
	return state.IsFirstShot() ? score + extraIfFirstRoll : score;	
}

auto single_rule = [](const Histogram& histogram, GameState& state) {
				if (histogram_has(histogram, 1))
				{		
					for (auto single : histogram.find(1)->second)
					{
						state.potentialScores.TryAssignScore(single, single);
					}
				}
};

auto pair_rule = [](const Histogram& histogram, GameState& state) {
				if (histogram_has(histogram, 2))
				{
					cout << "PAIR" << endl;				
					for (auto pair : histogram.find(2)->second)
					{
						state.potentialScores.TryAssignScore(pair, 2 * pair);
					}
				}
};

auto dpair_rule = MAKE_RULE(
				if ( (histogram_has(histogram, 2)) && histogram.find(2)->second.size()==2)
					cout << "DOULE PAIR" << endl;
				);

auto tris_rule = MAKE_RULE(
				if (histogram_has(histogram, 3))
				{
					cout << "TRIS" << endl;	
					auto trisValue = histogram.find(3)->second.front();
					state.potentialScores.TryAssignScore(trisValue, 3 * trisValue);
				}
				);

auto full_rule = MAKE_RULE( 
				if (histogram_has(histogram, 2) && histogram_has(histogram, 3))
				{
					cout << "FULL" << endl;
					state.potentialScores.TryAssignScore(Scores::full, Score(30, state));
				}
				);

auto poker_rule = MAKE_RULE( 
				if (histogram_has(histogram, 4))
				{
					cout << "POKER" << endl;	
					state.potentialScores.TryAssignScore(Scores::poker, Score(40, state));
					auto pokerValue = histogram.find(4)->second.front();
					state.potentialScores.TryAssignScore(pokerValue, 4 * pokerValue);
				}
				);

auto straight_rule = MAKE_RULE( 
				if ( (histogram.size() == 1) && histogram_has(histogram, 1) )
				{
					cout << "STRAIGHT" << endl;
					state.potentialScores.TryAssignScore(Scores::straight, Score(20, state));
				}
				);

auto generala_rule = MAKE_RULE( 
				if (histogram_has(histogram, 5))
				{
					cout << "GENERALA" << endl;
					state.potentialScores.TryAssignScore(Scores::generala, Score(50, state));
					auto generalaValue = histogram.find(5)->second.front();
					state.potentialScores.TryAssignScore(generalaValue, 5 * generalaValue);
				}
				);

auto dgenerala_rule = MAKE_RULE( 
				if (histogram_has(histogram, 5) && state.currentScores.HasScore(Scores::generala))
				{
					cout << "DOUBLE GENERALA" << endl;
					state.potentialScores.TryAssignScore(Scores::double_generala, Score(100, state));
					auto generalaValue = histogram.find(5)->second.front();
					state.potentialScores.TryAssignScore(generalaValue, 5 * generalaValue);
				}
				);

vector<Rule> RuleGenerator::GenerateRules()
{
	vector<Rule> rules;

	rules.push_back(single_rule);
	rules.push_back(pair_rule);
	rules.push_back(dpair_rule);
	rules.push_back(tris_rule);
	rules.push_back(full_rule);
	rules.push_back(poker_rule);
	rules.push_back(straight_rule);
	rules.push_back(generala_rule);
	rules.push_back(dgenerala_rule);

	return rules;
}
