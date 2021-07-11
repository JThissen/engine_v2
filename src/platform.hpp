#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
  #ifdef _WIN64
    #define ENGINE_WINDOWS_64
  #else
    #error "Windows 32-bit is not supported."
  #endif
#elif __APPLE__
  #error "Apple-based platform is not supported."
#elif defined(__ANDROID__)
  #define ENGINE_ANDROID
  #error "Android is not supported."
#elif defined(__linux__)
  #define ENGINE_LINUX
  #error "Linux is not supported."
#else
  #error "Could not identify compiler."
#endif
