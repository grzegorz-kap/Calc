#pragma once

#ifdef CALC_EXPORTS
#define CALC_API __declspec (dllexport)
#else
#define CALC_API __declspec (dllimport)
#endif

#define KLAB_TEST

#ifdef KLAB_TEST
#define CALC_TEST_API  CALC_API
#else
#define CALC_TEST_API
#endif