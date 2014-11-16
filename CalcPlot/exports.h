#ifdef CALCPLOT_EXPORTS
#define CALCPLOT_API __declspec (dllexport)
#else
#define CALCPLOT_API __declspec (dllimport)
#endif