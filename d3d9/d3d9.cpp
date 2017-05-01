/*
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
UINT_PTR mProcs[18] = {0};

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

extern "C" __declspec(naked) void __stdcall D3DPERF_BeginEvent_wrapper(){__asm{jmp mProcs[0*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_EndEvent_wrapper(){__asm{jmp mProcs[1*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_GetStatus_wrapper(){__asm{jmp mProcs[2*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_QueryRepeatFrame_wrapper(){__asm{jmp mProcs[3*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_SetMarker_wrapper(){__asm{jmp mProcs[4*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_SetOptions_wrapper(){__asm{jmp mProcs[5*4]}}
extern "C" __declspec(naked) void __stdcall D3DPERF_SetRegion_wrapper(){__asm{jmp mProcs[6*4]}}
extern "C" __declspec(naked) void __stdcall DebugSetLevel_wrapper(){__asm{jmp mProcs[7*4]}}
extern "C" __declspec(naked) void __stdcall DebugSetMute_wrapper(){__asm{jmp mProcs[8*4]}}
extern "C" __declspec(naked) void __stdcall Direct3D9EnableMaximizedWindowedModeShim_wrapper(){__asm{jmp mProcs[9*4]}}
extern "C" __declspec(naked) void __stdcall Direct3DCreate9_wrapper(){__asm{jmp mProcs[10*4]}}
extern "C" __declspec(naked) void __stdcall Direct3DCreate9Ex_wrapper(){__asm{jmp mProcs[11*4]}}
extern "C" __declspec(naked) void __stdcall Direct3DShaderValidatorCreate9_wrapper(){__asm{jmp mProcs[12*4]}}
extern "C" __declspec(naked) void __stdcall PSGPError_wrapper(){__asm{jmp mProcs[13*4]}}
extern "C" __declspec(naked) void __stdcall PSGPSampleTexture_wrapper(){__asm{jmp mProcs[14*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal16(){__asm{jmp mProcs[15*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal17(){__asm{jmp mProcs[16*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal18(){__asm{jmp mProcs[17*4]}}


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

