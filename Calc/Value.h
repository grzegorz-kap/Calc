#pragma once
#include "Numeric.h"

namespace PR
{
	template< class T>
	class Value :
		public Numeric<Value<T>>
	{
		T val;
	public:
		Value(){};
		Value(const T &b) : val(b){};
		~Value(){};

		template <class U>
		auto operator + (const Value<U> &b) const
			->Value < decltype(val + b.val) >
		{
			return Value<decltype(val + b.val)>(val + b.val);
		}
		
		/*virtual shared_ptr<Numeric<T>> operator + (const shared_ptr<Numeric<T>> &b) const  override
		{
			return nullptr;
		}

		

		*/

		template <class U>
		operator Value<U>() const
		{
			return Value<U>(val);
		}


		template <class U>
		friend class Value;
	};

}
