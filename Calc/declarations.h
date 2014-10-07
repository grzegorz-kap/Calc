#pragma once

#include <vector>
#include <memory>

namespace PR
{
	class Token;
	class Data;

#define INSTRUCTION std::vector<std::shared_ptr<Token>> 
#define CODE std::vector<std::vector<std::shared_ptr<Token>>> 
#define STACK std::vector<std::shared_ptr<Data>>

}
