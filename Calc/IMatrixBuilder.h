#pragma once

#include <memory>
#include <functional>

using std::shared_ptr;
using std::unique_ptr;

#include "Data.h"

namespace PR
{
	template <class X>
	class MatrixBuilder;

	class IMatrixBuilder
	{
	public:
		IMatrixBuilder();
		~IMatrixBuilder();

		virtual void add(shared_ptr<Data> &data) = 0;
		virtual shared_ptr<Data> getPtr() const = 0;
		virtual void setAndCheckSize(bool f = true) = 0;
	};

}
