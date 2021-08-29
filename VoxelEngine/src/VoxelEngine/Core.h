#pragma once

#ifdef VE_PLATFORM_WINDOWS
	#ifdef VE_BUILD_DLL
		#define VOXELENGINE_API _declspec(dllexport)
	#else
		#define VOXELENGINE_API _declspec(dllimport)
	#endif
#else
	#error Unsupported platform!
#endif