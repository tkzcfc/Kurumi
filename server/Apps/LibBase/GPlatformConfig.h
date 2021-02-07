#pragma once


#define G_PLATFORM_UNKNOWN            0
#define G_PLATFORM_WIN32              1
#define G_PLATFORM_MAC                2
#define G_PLATFORM_LINUX              3

#define G_TARGET_PLATFORM             G_PLATFORM_UNKNOWN

// Apple
#if defined(__APPLE__) && !defined(ANDROID) // exclude android for binding generator.
    #include <TargetConditionals.h>
    #undef  G_TARGET_PLATFORM
	#define G_TARGET_PLATFORM         G_PLATFORM_MAC
#endif

// win32
#if defined(_WIN32) && defined(_WINDOWS)
    #undef  G_TARGET_PLATFORM
    #define G_TARGET_PLATFORM         G_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
    #undef  G_TARGET_PLATFORM
    #define G_TARGET_PLATFORM         G_PLATFORM_LINUX
#endif

#if ! G_TARGET_PLATFORM
    #error  "Cannot recognize the target platform"
#endif

