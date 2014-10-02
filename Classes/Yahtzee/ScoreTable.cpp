#include "ScoreTable.h"

#include <iostream>
#include <numeric>

using namespace std;

ScoreTable::ScoreTable()
{
	Score score = {false, 0};
	for (const auto& name : score_names)
	{
		scores.insert(make_pair( name, score ));	
	}
}

unsigned short ScoreTable::TotalScore() const
{
	return accumulate(begin(scores), end(scores), 0, [](unsigned short current, const pair<string, Score>& score)
	{
		return current + score.second.value;
	});
}

bool ScoreTable::HasScore(Scores::ScoreName scoreName) const 
{
	return scores.at(score_names[scoreName]).value != 0;
}

void ScoreTable::AssignFrom(const ScoreTable& other, const std::string& scoreName)
{
	auto& dieActualScore = scores.at(scoreName);
	if (false == dieActualScore.assigned) 
	{
		dieActualScore.value = other.scores.at(scoreName).value;
		dieActualScore.assigned = true;
	}
}

void ScoreTable::TryAssignScore(unsigned short dieValue, size_t score)
{
	const auto dieValueToStr = to_string(dieValue);
	AssignScoreIfNotAssigned(dieValueToStr, score);
}

void ScoreTable::TryAssignScore(Scores::ScoreName scoreName, size_t score)
{
	AssignScoreIfNotAssigned(score_names[scoreName], score);
}

void ScoreTable::AssignScoreIfNotAssigned(const string& name, size_t score)
{
	auto& dieActualScore = scores.at(name);
	if (false == dieActualScore.assigned) 
	{
		dieActualScore.value = score;
	}
}

ostream& operator<<(ostream& stream, const ScoreTable& table) 
{
	for (const auto& score : table.scores)
	{
		stream << score.first << " -> " << score.second.value << (score.second.assigned ? "" : " *") << endl;
	}
	return stream;
}