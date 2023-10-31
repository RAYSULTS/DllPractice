#pragma once

//#ifdef Dllexport
//#define Dllexport __declspec(dllexport)
//#else
//#define DllImport __declspec(dllimport)
//#endif

/// Dll Macros Import/Export
#define DllExport __declspec(dllexport)
#define DllImport __declspec(dllimport)

extern "C" DllExport void PrintDevices();

extern "C" DllExport void PrintEndpointNames();


extern "C" DllExport void SetDefaultDevices(LPCWSTR devID, int erole);
extern "C" DllExport void PrintDefaultAudioEndpoint(int input);

extern "C" DllExport void PrintDefaultAudioEndpoint(int input);

void PrintDefaultAudioEndpoint(int input);
void SetDefaultDevices(LPCWSTR devID, int erole);

