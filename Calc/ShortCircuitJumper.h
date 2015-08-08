#pragma once
#include "Token.h"

namespace PR
{
	class ShortCircuitJumper :
		public Token
	{
	public:
		ShortCircuitJumper(TOKEN_CLASS _class);
		~ShortCircuitJumper();

		int getJumpOnFalse() const;
		int getJumpOnTrue() const;
		int getJumpOn(bool val) const;
		int getJumpOn(TOKEN_CLASS _class) const;

		void setJumpOnFalse(int val);
		void setJumpOnTrue(int val);

	private:
		int jump_on_false;
		int jump_on_true;
	};
}
