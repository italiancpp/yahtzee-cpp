#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Rule.h"

class RuleGenerator
{
public:
	static std::vector<Rule> GenerateRules();
};

