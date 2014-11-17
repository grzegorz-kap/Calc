#pragma once

#include <memory>
#include <functional>
#include <unordered_map>

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

		static const std::unordered_map<TYPE, TYPE> TYPES;
		TYPE getAssociatedType(const TYPE &_type);
	};

}
