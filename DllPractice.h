// DllPractice.h - Contains declarations of math functions
#pragma once

#ifdef DllPractice_EXPORTS
#define DllPractice_API __declspec(dllexport)
#else
#define DllPractice_API __declspec(dllimport)
#endif

extern "C" DllPractice_API void PrintDevices();

extern "C" DllPractice_API void PrintEndpointNames();


extern "C" DllPractice_API void SetDefaultDevices(LPCWSTR devID);
extern "C" DllPractice_API void PrintDefaultAudioEndpoint();




