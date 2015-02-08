// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


/*!
\mainpage KLab - Interpreter operacji matematycznych.
\author Grzegorz Kapica
\date 08.02.2015
\version 1.0
\section etykieta-zalozenia Przeznaczenie aplikacji
KLab jest aplikacja sluzaca do przeprowadzanie obliczen numerycznych.
Obsluguje ona podstawowe konstrukcje jezyka Matlab.
*/

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

