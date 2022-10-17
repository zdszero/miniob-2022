#pragma once

#include <cstdio>
#include <cassert>

#define DEBUG 1

#if defined(DEBUG) && DEBUG > 0
#define DPrintf(fmt, args...) fprintf(stderr, "DEBUG: " fmt, ##args)
#else
#define DPrintf(fmt, args...) /* Don't do anything in release builds */
#endif

#define ASSERT(expr, message) assert((expr) && (message))
