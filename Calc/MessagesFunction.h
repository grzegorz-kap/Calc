#include "Function.h"

namespace KLab
{
	class ErrorFunction : public Function
	{
	public:
		ErrorFunction();
		~ErrorFunction();
		virtual shared_ptr<Data> run() override;
	};
}