#ifndef BUNNY_DEBUG_H
#define BUNNY_DEBUG_H

#ifdef BUNNY_DEBUG
#include <stdio.h>
#define BUNNY_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define BUNNY_DEBUG_PRINT(...)
#endif  // BUNNY_DEBUG

#endif  // BUNNY_DEBUG_H