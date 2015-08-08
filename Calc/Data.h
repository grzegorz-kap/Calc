#ifndef DATA_H
#define DATA_H

#pragma once
#include "export.h"

#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include <boost\multiprecision\cpp_bin_float.hpp>

using namespace boost::multiprecision;

using std::shared_ptr;
using std::make_shared;
using std::vector;

#include "UnimplementedException.h"
#include "CastException.h"
#include "TokensTypes.h"

namespace KLab
{
	typedef cpp_bin_float_100 hdouble;

	template <class T> class Numeric;
	template <class T> class Matrix;
	template <class T> class ComplexNumber;
	class String;
	class Token;
	class Output;

	enum class TYPE : int
	{
		UNKNOWN,
		TOKEN,
		OUTPUT,
		STRING,
		DOUBLE,
		R_DOUBLE,
		M_DOUBLE,
		RM_DOUBLE
	};

	//! Interfejs dla typow danych programu.
	class   Data
	{
	protected:

	public:
		Data();
		~Data();
		TYPE _type; //!< Typ wartosci.
		bool _updated; //!< Flaga modyfikacji.
		bool _added;   //!< Flaga dodania.
		bool _temp;    //!< Obiekt tymczasowy.

		const static std::unordered_map<std::type_index, TYPE> TYPE_MAP; //!< mapa typow danych.
		const static std::unordered_map < TYPE, string > TYPE_NAME_MAP; //!< mapa nazw typow.

		static TYPE find_type(const std::type_index &idx); //!< Pobranie elementu z mapy typow danych.
		static const string & find_name(const TYPE &type); //!< Pobranie nazwy typu.

		virtual bool isMatrix() const{ return false; }
		virtual bool isComplexNumber() const{ return false; }
		virtual bool isScalar() const { return false; }
		virtual bool isInteger() const { return false; }
		virtual bool isReal() const { return false; }

		virtual int toInteger() const;

		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator - (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator * (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator / (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator | (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator & (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator ! () const;
		virtual shared_ptr<Data> exponentiation(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> mexponentiation(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator - () const;
		virtual shared_ptr<Data> times(shared_ptr<Data> &) const;
		virtual shared_ptr<Data> rdivide(shared_ptr<Data> &) const;
		virtual shared_ptr<Data> eq(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> ge(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> gt(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> le(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> lt(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> ne(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> transposition() const;
		virtual shared_ptr<Data> ctransposition() const;
		virtual shared_ptr<Data> log() const;
		virtual shared_ptr<Data> log(shared_ptr<Data> &) const;
		virtual shared_ptr<Data> log2() const;
		virtual shared_ptr<Data> log10() const;
		virtual shared_ptr<Data> sqrt() const;
		virtual void lu(shared_ptr<Data> &) const;
		virtual void  lu(shared_ptr<Data> &, shared_ptr<Data> &) const;
		virtual void  lu(shared_ptr<Data> &, shared_ptr<Data> &, shared_ptr<Data> &) const;
		virtual shared_ptr<Data> cholesky() const;
		virtual shared_ptr<Data> url(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> det() const;
		virtual shared_ptr<Data> inv() const;
		virtual shared_ptr<Data> sin() const;
		virtual shared_ptr<Data> cos() const;
		virtual shared_ptr<Data> tan() const;
		virtual shared_ptr<Data> cot() const;
		virtual shared_ptr<Data> conj() const;
		virtual shared_ptr<Data> cfix() const;
		virtual shared_ptr<Data> cfloor() const;
		virtual shared_ptr<Data> cmod(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> cceil() const;
		virtual shared_ptr<Data> cround() const;
		virtual bool operator == (const bool &b) const;
		virtual string toString() const;
		virtual string toStringCommpact() const;
		virtual string toHtml() const;
		virtual shared_ptr<Data> get_rows() const;
		virtual shared_ptr<Data> get_cols() const;
		virtual TYPE max_type() const;
		virtual Token * cast_token();
		virtual bool isNumeric() const;
		virtual bool isOutput() const;
		virtual shared_ptr<Data> getAt() const;
		virtual shared_ptr<Data> getAt(shared_ptr<Data>&) const;
		virtual shared_ptr<Data> getAt(shared_ptr<Data>&, shared_ptr<Data>&) const;
		virtual void assignAt(shared_ptr<Data>& data);
		virtual void assignAt(shared_ptr<Data>& cells, shared_ptr<Data>& data);
		virtual void assignAt(shared_ptr<Data>& rows, shared_ptr<Data> & colls, shared_ptr<Data>& data);
		virtual Output * cast_output();
		virtual bool isToken(TOKEN_CLASS _class)const{ return false; }
		virtual shared_ptr<Data> createVector(shared_ptr<Data> &end) const;
		virtual shared_ptr<Data> createVector(shared_ptr<Data> &step, shared_ptr<Data> &end) const;
		virtual int get_cols_int() const { return 0; }
		virtual int get_rows_int() const { return 0; }
		virtual string get_cell_string(int i, int j) const{ return ""; }
		virtual shared_ptr<Data> getColumn(int idx) const;
		virtual vector<double> toDoubleVector() const;
		virtual vector<double> toDoubleVectorAll() const;
		virtual string minValueString() const;
		virtual string maxValueString() const;
		virtual string getValueInfoString() const;
		virtual string getTypeName() const;
		virtual shared_ptr<Data> copy() const;
		virtual shared_ptr<Data> get_single_index() const; /* For indexing */
		virtual shared_ptr<Data> get_rows_index() const; /* For indexing */
		virtual shared_ptr<Data> get_cols_index() const; /* For indexing */

		//! Konwertuje typ wartosci na inny.
		//! \param T typu do ktorego odbedzie sie konwersja.
		template<class T>
		shared_ptr<Numeric<T>>  convert_numeric()
		{
			switch (this->_type)
			{
			case TYPE::M_DOUBLE:
				return make_shared<T>(*dynamic_cast<Matrix<double> *>(this));
			case TYPE::DOUBLE:
				return make_shared<T>(*dynamic_cast<ComplexNumber<double> *>(this));
			case TYPE::R_DOUBLE:
				return make_shared<T>(*dynamic_cast<ComplexNumber<hdouble> *>(this));
			case TYPE::RM_DOUBLE:
				return make_shared<T>(*dynamic_cast<Matrix<hdouble> *>(this));

			default:
				throw CastException(prepareCastError());
			}
		}
		template<class T>
		Numeric<T> * cast_numeric()
		{
			return dynamic_cast<Numeric<T> *> (this);
		}

	private:
		string prepareCastError();
	};
};

#endif
