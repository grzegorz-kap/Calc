#ifdef CALC_EXPORTS
#define CALC_API __declspec (dllexport)
#else
#define CALC_API __declspec (dllimport)
#endif