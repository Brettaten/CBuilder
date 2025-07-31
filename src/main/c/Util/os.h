#ifndef HEADERGUARDOS
#define HEADERGUARDOS

#ifdef _WIN32
    #define OS "win"
#elif __unix__
    #define OS "unix"
#else
    #define OS "null"
#endif

#endif