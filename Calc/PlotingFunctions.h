#include "Function.h"
#include "GraphDrawer.h"

namespace KLab
{
	class PlotFunction : public Function
	{
	public:
		PlotFunction();
		~PlotFunction();
		virtual shared_ptr<Data> run() override;
	};

	class Plot3Function : public Function
	{
	public:
		Plot3Function();
		~Plot3Function();

		shared_ptr<Data> run() override;
	};

	class SurfaceFunction : public Function
	{
	public:
		SurfaceFunction();
		~SurfaceFunction();

		shared_ptr<Data> run() override;
	};
}