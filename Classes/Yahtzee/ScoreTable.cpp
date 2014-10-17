#include "ScoreTable.h"

#include <numeric>

using namespace std;

ScoreTable::ScoreTable()
{
	Score score = { false, 0 };
	// INVECCHIAMENTO
	for (size_t i = 0; i < score_names.size(); ++i)
		scores.insert(make_pair(score_names[i], score));

	/*for (const auto& name : score_names)
	{
		scores.insert(make_pair( name, score ));	
	}*/
}

// INVECCHIAMENTO
ScoreTable::ScoreTable(const ScoreTable& other)
	: scores(other.scores)
{

}

unsigned short ScoreTable::TotalScore() const
{
	// INVECCHIAMENTO
	unsigned short tot = 0;
	for (map<std::string, Score>::const_iterator it = scores.begin(); it != scores.end(); ++it)
		tot += it->second.value;
	return tot;
	/*return accumulate(begin(scores), end(scores), 0, [](unsigned short current, const pair<string, Score>& score)
	{
		return current + score.second.value;
	});*/
}

bool ScoreTable::HasScore(Scores::ScoreName scoreName) const 
{
	return scores.at(score_names[scoreName]).value != 0;
}

void ScoreTable::AssignFrom(const ScoreTable& other, const std::string& scoreName)
{
	// INVECCHIAMENTO
	Score& dieActualScore = scores.at(scoreName);
	//auto& dieActualScore = scores.at(scoreName);
	if (false == dieActualScore.assigned) 
	{
		dieActualScore.value = other.scores.at(scoreName).value;
		dieActualScore.assigned = true;
	}
}

void ScoreTable::TryAssignScore(unsigned short dieValue, size_t score)
{
	// INVECCHIAMENTO
	string dieValueToStr = to_string(dieValue);
	/*const auto dieValueToStr = to_string(dieValue);*/
	AssignScoreIfNotAssigned(dieValueToStr, score);
}

void ScoreTable::TryAssignScore(Scores::ScoreName scoreName, size_t score)
{
	AssignScoreIfNotAssigned(score_names[scoreName], score);
}

void ScoreTable::AssignScoreIfNotAssigned(const string& name, size_t score)
{
	// INVECCHIAMENTO
	Score& dieActualScore = scores.at(name);
	if (false == dieActualScore.assigned) 
	{
		dieActualScore.value = score;
	}
}

//ostream& operator<<(ostream& stream, const ScoreTable& table)
//{
//	// INVECCHIAMENTO
//	for (map<std::string, Score>::const_iterator it = table.scores.begin(); it != table.scores.end(); ++it)
//		stream << it->first << " -> " << it->second.value << (it->second.assigned ? "" : " *") << endl;
//	/*for (const auto& score : table.scores)
//	{
//		stream << score.first << " -> " << score.second.value << (score.second.assigned ? "" : " *") << endl;
//	}*/
//	return stream;
//}