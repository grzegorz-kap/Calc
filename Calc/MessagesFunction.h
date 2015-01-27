#include "Function.h"

namespace PR
{
	class ErrorFunction : public Function
	{
	public:
		ErrorFunction();
		~ErrorFunction();
		virtual shared_ptr<Data> run() override;
	};
}