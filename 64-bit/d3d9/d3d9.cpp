/*
	d3d9.dll Preloader (64-bit)

	Simple d3d9.dll wrapper used by an external program to load
	d3d9.dll from the system directory instead of the local
	directory to circumvent any existing d3d9.dll wrappers that
	may cause incompatibility issues. This wrapper does not
	modify or add to the functionality of the original d3d9.dll.

	Author: Sean Pesce
*/

#include <Windows.h>
#include <stdio.h>

HINSTANCE mHinst = 0, mHinstDLL = 0;
extern "C" UINT_PTR mProcs[18] = {0};

void LoadOriginalDll();

LPCSTR mImportNames[] = {"D3DPERF_BeginEvent", "D3DPERF_EndEvent", "D3DPERF_GetStatus", "D3DPERF_QueryRepeatFrame", "D3DPERF_SetMarker", "D3DPERF_SetOptions", "D3DPERF_SetRegion", "DebugSetLevel", "DebugSetMute", "Direct3D9EnableMaximizedWindowedModeShim", "Direct3DCreate9", "Direct3DCreate9Ex", "Direct3DShaderValidatorCreate9", "PSGPError", "PSGPSampleTexture", (LPCSTR)16, (LPCSTR)17, (LPCSTR)18};
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if ( fdwReason == DLL_PROCESS_ATTACH ) {
		LoadOriginalDll();
		for ( int i = 0; i < 18; i++ )
			mProcs[ i ] = (UINT_PTR)GetProcAddress( mHinstDLL, mImportNames[ i ] );
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		FreeLibrary( mHinstDLL );
	}
	return ( TRUE );
}

extern "C" void D3DPERF_BeginEvent_wrapper();
extern "C" void D3DPERF_EndEvent_wrapper();
extern "C" void D3DPERF_GetStatus_wrapper();
extern "C" void D3DPERF_QueryRepeatFrame_wrapper();
extern "C" void D3DPERF_SetMarker_wrapper();
extern "C" void D3DPERF_SetOptions_wrapper();
extern "C" void D3DPERF_SetRegion_wrapper();
extern "C" void DebugSetLevel_wrapper();
extern "C" void DebugSetMute_wrapper();
extern "C" void Direct3D9EnableMaximizedWindowedModeShim_wrapper();
extern "C" void Direct3DCreate9_wrapper();
extern "C" void Direct3DCreate9Ex_wrapper();
extern "C" void Direct3DShaderValidatorCreate9_wrapper();
extern "C" void PSGPError_wrapper();
extern "C" void PSGPSampleTexture_wrapper();
extern "C" void ExportByOrdinal16();
extern "C" void ExportByOrdinal17();
extern "C" void ExportByOrdinal18();


// Loads the original DLL from the default system directory
//	Function originally written by Michael Koch
void LoadOriginalDll()
{
	char buffer[MAX_PATH];

	// Get path to system dir and to d3d9.dll
	GetSystemDirectory(buffer, MAX_PATH);

	// Append DLL name
	strcat_s(buffer, "\\d3d9.dll");

	// Try to load the system's d3d9.dll, if pointer empty
	if (!mHinstDLL) mHinstDLL = LoadLibrary(buffer);

	// Debug
	if (!mHinstDLL)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		ExitProcess(0); // Exit the hard way
	}
}

