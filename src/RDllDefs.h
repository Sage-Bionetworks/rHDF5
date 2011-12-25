#ifndef R_DLL_DEFS_INC
#define R_DLL_DEFS_INC

#if defined WIN32
    #ifdef R_DLL_EXPORTS
        #define R_DLL_API __declspec(dllexport)
    #else
        #define R_DLL_API __declspec(dllimport)
    #endif
#else
    #define R_DLL_API
#endif

#endif
