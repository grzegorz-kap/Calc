#pragma once

#include <memory>

using std::unique_ptr;


namespace PR
{
	template <class T>
	class Numeric;

	class Data
	{
	public:
		Data();
		~Data();

		virtual unique_ptr<Data> operator + (const unique_ptr<Data> &b) const = 0;

		template<class T>
		Numeric<T> * cast_numeric()
		{
			return static_cast<Numeric<T> *>(this);
		}
	};

}
