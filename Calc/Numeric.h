#pragma once

#include <memory>

using std::shared_ptr;
using std::make_unique;

#include  "Data.h"
#include "Mathematic.h"
#include "MatrixUtils.h"

namespace PR
{
	template <class A>
	class Matrix;

	template <class A>
	class ComplexNumber;

	template <class T>
	class Numeric
		:public Data
	{
	public:

		Numeric()
		{
		}

		~Numeric()
		{
		}

		virtual bool isNumeric() const override
		{
			return true;
		}

		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() + *(b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> operator - (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() - *(b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> operator * (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() * *(b->cast_numeric<T>()->get_derived()));
		}


		virtual shared_ptr<Data> operator / (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() / *(b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> exponentiation(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(Mathematic::power(*get_derived(), *b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> mexponentiation(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(Mathematic::mpower(*get_derived(), *b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> log() const override
		{
			return make_shared<T>(Mathematic::logarithm(*get_derived()));
		}

		virtual shared_ptr<Data> log2() const override
		{
			return make_shared<T>(Mathematic::logarithm2(*get_derived()));
		}

		virtual shared_ptr<Data> log10() const override
		{
			return make_shared<T>(Mathematic::logarithm10(*get_derived()));
		}

		virtual shared_ptr<Data> log(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(Mathematic::logarithm(*get_derived(), *b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> sin() const override
		{
			return make_shared<T>(Mathematic::sinus(*get_derived()));
		}

		virtual shared_ptr<Data> cos() const override
		{
			return make_shared<T>(Mathematic::cosinus(*get_derived()));
		}

		virtual shared_ptr<Data> tan() const override
		{
			return make_shared<T>(Mathematic::tangens(*get_derived()));
		}

		virtual void lu(shared_ptr<Data> &dest) const override
		{
			T * ptr = nullptr;
			MatrixUtils::lu(*get_derived(),&ptr);
			dest = shared_ptr<Data>(ptr);
		}

		virtual void lu(shared_ptr<Data> &l,shared_ptr<Data> &u) const override
		{
			T * ptr2 = nullptr;
			T * ptr1 = nullptr;
			MatrixUtils::lu(*get_derived(), &ptr1,&ptr2);
			l = shared_ptr<Data>(ptr1);
			u = shared_ptr<Data>(ptr2);
		}

		virtual void lu(shared_ptr<Data> &l, shared_ptr<Data> &u, shared_ptr<Data> &p) const override
		{
			T *ptr3 = nullptr;
			T * ptr2 = nullptr;
			T * ptr1 = nullptr;
			MatrixUtils::lu(*get_derived(), &ptr1, &ptr2,&ptr3);
			l = shared_ptr<Data>(ptr1);
			u = shared_ptr<Data>(ptr2);
			p = shared_ptr<Data>(ptr3);
		}

		virtual shared_ptr<Data> det() const override
		{
			return make_shared<T>(MatrixUtils::det(*get_derived()));
		}

		virtual shared_ptr<Data> inv() const override
		{
			return make_shared<T>(MatrixUtils::inv(*get_derived()));
		}

		virtual shared_ptr<Data> operator -() const override
		{
			return make_shared<T>(get_derived()->neg());
		}

		virtual shared_ptr<Data> times(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(get_derived()->times(*(b->cast_numeric<T>()->get_derived())));
		}

		virtual shared_ptr<Data> rdivide(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(get_derived()->rdivide(*(b->cast_numeric<T>()->get_derived())));
		}

		virtual shared_ptr<Data> eq(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() == *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> ge(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() >= *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> gt(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() > *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> le(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() <= *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> lt(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() < *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> ne(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() != *b->cast_numeric<T>()->get_derived());
		}

		virtual bool operator == (const bool &b) const override
		{
			return false;
		}

		virtual shared_ptr<Data> get_rows() const override
		{
			return make_shared<T>(get_derived()->rows());
		}

		virtual shared_ptr<Data> get_cols() const override
		{
			return make_shared<T>(get_derived()->cols());
		}

		virtual shared_ptr<Data> transposition() const override
		{
			return make_shared<T>(get_derived()->transpose());
		}

		virtual shared_ptr<Data> getAt() const override
		{
			return make_shared<T>(*get_derived());
		}

		virtual shared_ptr<Data> getAt(shared_ptr<Data> &cells) const override
		{
			if (cells->isToken(TOKEN_CLASS::MATRIX_ALL))
				cells = getSingleIndex();
			return make_shared<T>(get_derived()->at(*cells->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> getAt(shared_ptr<Data> &first, shared_ptr<Data> &second) const override
		{
			if (first->isToken(TOKEN_CLASS::MATRIX_ALL))
				first = getRowsIndexes();
			if (second->isToken(TOKEN_CLASS::MATRIX_ALL))
				second = getColsIndexes();
			return make_shared<T>(get_derived()->at(
				*first->cast_numeric<T>()->get_derived(),
				*second->cast_numeric<T>()->get_derived()
				));
		}

		virtual void assignAt(shared_ptr<Data>& data)  override
		{
			get_derived_non_const()->assign(*data->cast_numeric<T>()->get_derived());
		}

		virtual void assignAt(shared_ptr<Data>& cells, shared_ptr<Data>& data) override
		{ 
			if (cells->isToken(TOKEN_CLASS::MATRIX_ALL))
				cells = getSingleIndex();
			get_derived_non_const()->assign(*cells->cast_numeric<T>()->get_derived(),*data->cast_numeric<T>()->get_derived());
		}

		virtual void assignAt(shared_ptr<Data>& rows, shared_ptr<Data>& cols, shared_ptr<Data>& data) override
		{
			if (rows->isToken(TOKEN_CLASS::MATRIX_ALL) && cols->isToken(TOKEN_CLASS::MATRIX_ALL))
			{
				cols = getColsIndexes();
				rows = getRowsIndexes();
			}
			else
			{
				if (rows->isToken(TOKEN_CLASS::MATRIX_ALL))
				{
					if (isEmpty())
						rows = getVectorForAssignment(data->cast_numeric<T>()->getRowsCountForEmptyMatrixAssignment());
					else
						rows = getRowsIndexes();
				}

				if (cols->isToken(TOKEN_CLASS::MATRIX_ALL))
				{
					if (isEmpty())
						cols = getVectorForAssignment(data->cast_numeric<T>()->getColsCountForEmptyMatrixAssignment());
					else
						cols = getColsIndexes();
				}
			}
			

			get_derived_non_const()->assign(*rows->cast_numeric<T>()->get_derived(),
				*cols->cast_numeric<T>()->get_derived(),
				*data->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> getColumn(int idx) const override
		{
			return make_shared<T>(get_derived()->atColumn(idx));
		}

		virtual bool isEmpty() const
		{
			return false;
		}

		virtual int getRowsCountForEmptyMatrixAssignment() const { return 1; }
		virtual int getColsCountForEmptyMatrixAssignment() const { return 1; }

		shared_ptr<Data> getRowsIndexes() const 
		{
			return make_shared<T>(get_derived()->getRowIndex());
		}

		shared_ptr<Data> getColsIndexes() const 
		{
			return make_shared<T>(get_derived()->getColIndex());
		}
		
		shared_ptr<Data> getSingleIndex() const 
		{
			return make_shared<T>(get_derived()->getIndexAll());
		}
		
		virtual shared_ptr<Data> createVector(shared_ptr<Data> &end) const override
		{
			return make_shared<T>(MatrixUtils::createVector(
				*get_derived(), 
				*end->cast_numeric<T>()->get_derived()
				));
		}

		virtual shared_ptr<Data> createVector(shared_ptr<Data> &step, shared_ptr<Data> &end) const override
		{
			return make_shared<T>(MatrixUtils::createVector(
				*get_derived(),
				*step->cast_numeric<T>()->get_derived(),
				*end->cast_numeric<T>()->get_derived()
				));
		}

	private:

		shared_ptr<Data> getVectorForAssignment(const int &stop) const
		{
			return make_shared<T>(get_derived()->getIndex(stop));
		}

		const T * get_derived() const
		{
			return dynamic_cast<const T *>(this);
		}

		T * get_derived_non_const()
		{
			return dynamic_cast<T *>(this);
		}

		template <class U>
		friend class Numeric;
	};

};
