#pragma once

#include "MatrixBuilder.h"

namespace KLab
{
	//! Fabryka implementacji budowania macierzy.
	class MatrixBuilderFactory
	{
	public:
		MatrixBuilderFactory() = delete;
		~MatrixBuilderFactory() = delete;

		//! Pobranie implementacji budowania macierzy.
		/*!
		* @param _type typ macierzy do zbudowania
		*/
		static unique_ptr<IMatrixBuilder> get(TYPE _type);
	};
}
