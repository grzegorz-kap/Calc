#pragma once

#include <vector>
#include <memory>
#include <string>

using std::vector;
using std::shared_ptr;
using std::string;

#include "Token.h"

namespace PR
{
	//! \brief Zawiera informacje o instrukcji for.
	//! Obiekty tej klasy sa tworzone na etapie parsowania instrukcji.
	class InstructionFor :
		public Token
	{
		vector<shared_ptr<Token>> onp;
		string name;
	public:
		InstructionFor();
		InstructionFor(const Token &token);
		~InstructionFor();

		//! Ustawia nazwe zmiennej bedacej iteratorem petli.
		void setName(const string &new_name);

		//! Ustawia wyrazenie stanowiace zestaw iterowanych wartosci.
		void setOnp(const vector<shared_ptr<Token>> &o);
		void setOnp(vector<shared_ptr<Token>> &&o);
		const vector<shared_ptr<Token>>& getOnp() const;
		virtual string getLexeme() const override;
	};
}
