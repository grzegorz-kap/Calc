#pragma once
#include "Function.h"
#include "GraphDrawer.h"
namespace PR
{
	class SurfaceFunction :
		public Function
	{
	public:
		SurfaceFunction();
		~SurfaceFunction();

		shared_ptr<Data> run() override;
	};

}
