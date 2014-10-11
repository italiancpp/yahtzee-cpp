#pragma once

#include <map>
#include <string>
#include <array>
#include "ScoreValues.h"

struct Score
{
	bool assigned;
	unsigned short value;
};

class ScoreTable
{
public:
	ScoreTable();
	~ScoreTable() {}
	// INVECCHIAMENTO
	ScoreTable(const ScoreTable& other);

	void TryAssignScore(unsigned short dieValue, size_t score);
	void TryAssignScore(Scores::ScoreName scoreName, size_t score);
	void AssignFrom(const ScoreTable& other, const std::string& score);
	bool HasScore(Scores::ScoreName scoreName) const;
	unsigned short TotalScore() const;

//	bool operator == (const ScoreTable& other) const
//	{
//		return scores == other.scores;
//	}

	friend std::ostream& operator<<(std::ostream& stream, const ScoreTable& table);
private:

	void AssignScoreIfNotAssigned(const std::string& name, size_t score);

	std::map<std::string, Score> scores;
};

std::ostream& operator<<(std::ostream& stream, const ScoreTable& table);