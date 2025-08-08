#ifndef HEADERGUARDOS
#define HEADERGUARDOS

#ifdef _WIN32
    #define WIN
#elif defined(__linux__)
    #define LINUX
#elif defined(__APPLE__)
    #define APPLE
#else
    #define OTHER
#endif

#endif