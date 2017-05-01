# d3d9.dll Preloader  
Author: Sean Pesce

Simple d3d9.dll wrapper used by programs to load d3d9.dll from the system directory instead of the local directory to circumvent any existing d3d9.dll wrappers that may cause incompatibility issues (such as PvP Watchdog for Dark Souls). This wrapper does not modify or add to the functionality of the original d3d9.dll.  

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
IntPtr d3d9_preload = Kernel32_LoadLib.LoadLibrary(@"d3d9_preloader.dll");
```  

## C++ Implementation

Include the Win32 API header in your project (`#include <Windows.h>`), and load the library at runtime, like so:  

```c++
LoadLibrary("d3d9_preloader.dll");
```  

