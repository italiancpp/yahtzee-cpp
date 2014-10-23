#include "ScoreTable.h"

#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

ScoreTable::ScoreTable()
{
	Score score = { false, 0 };
	for (size_t i = 0; i < score_names.size(); ++i)
		scores.insert(make_pair(score_names[i], score));
}

ScoreTable::ScoreTable(const ScoreTable& other)
	: scores(other.scores)
{

}

unsigned short ScoreTable::TotalScore() const
{
	unsigned short tot = 0;
	for (map<std::string, Score>::const_iterator it = scores.begin(); it != scores.end(); ++it)
		tot += it->second.value;
	return tot;
}

bool ScoreTable::HasScore(Scores::ScoreName scoreName) const 
{
	return scores.at(score_names[scoreName]).value != 0;
}

void ScoreTable::AssignFrom(const ScoreTable& other, const std::string& scoreName)
{
	Score& dieActualScore = scores.at(scoreName);
	
	if (false == dieActualScore.assigned) 
	{
		dieActualScore.value = other.scores.at(scoreName).value;
		dieActualScore.assigned = true;
	}
}

void ScoreTable::TryAssignScore(unsigned short dieValue, size_t score)
{
	string dieValueToStr = to_string(dieValue);
	AssignScoreIfNotAssigned(dieValueToStr, score);
}

void ScoreTable::TryAssignScore(Scores::ScoreName scoreName, size_t score)
{
	AssignScoreIfNotAssigned(score_names[scoreName], score);
}

void ScoreTable::AssignScoreIfNotAssigned(const string& name, size_t score)
{
	Score& dieActualScore = scores.at(name);
	if (false == dieActualScore.assigned) 
	{
		dieActualScore.value = score;
	}
}

ostream& operator<<(ostream& stream, const ScoreTable& table)
{
	for (std::map<std::string, Score>::const_iterator it = table.scores.begin(); it != table.scores.end(); ++it)
		stream << it->first << " -> " << it->second.value << (it->second.assigned ? "" : " *") << std::endl;
	return stream;
}

void ScoreTable::AssignFrom(const ScoreTable &other, Scores::ScoreName score)
{
	auto it = std::find_if(
		scores.begin(),
		scores.end(),
		[=](const std::pair<const std::string, Score> &pair)
		{
			return pair.second.value == score;
		});

	AssignFrom(other, it->first);
}
