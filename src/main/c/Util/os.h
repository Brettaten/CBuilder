#ifndef HEADERGUARDOS
#define HEADERGUARDOS

#ifdef _WIN32
    #define WIN
#elif __unix__
    #define UNIX
#else
    #define OTHER
#endif

#endif