# Preloader for d3d9.dll and dxgi.dll  
Author: Sean Pesce

Simple d3d9.dll wrapper used by programs to load d3d9.dll and dxgi.dll from the system directory instead of the local directory to circumvent any existing wrappers for these DLLs that may cause incompatibility issues (such as SweetFX or PvP Watchdog for Dark Souls). This wrapper does not modify or add to the functionality of the original d3d9.dll.  

## C# Implementation  

First, add this class to your project:  

```c#
static class Kernel32_LoadLib
{
  [System.Runtime.InteropServices.DllImport("kernel32.dll")]
  public static extern IntPtr LoadLibrary(string dllToLoad);
}
```

Then, load the library at runtime, like so:  

```c#
IntPtr dll_preload = Kernel32_LoadLib.LoadLibrary(@"dll_preloader.dll");
```  

## C++ Implementation

Include the Win32 API header in your project (`#include <Windows.h>`), and load the library at runtime, like so:  

```c++
LoadLibrary("dll_preloader.dll");
```  

