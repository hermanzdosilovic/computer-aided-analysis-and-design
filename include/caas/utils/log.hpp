#pragma once

#include <cstdio>

#ifdef COLORED_LOG
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED "\033[31m"
#define COLOR_DEFAULT "\033[0m"
#else
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_RED ""
#define COLOR_DEFAULT ""
#endif

#define NOOP ( ( void ) 0 )
#define DETAILS( file ) std::fprintf( file, "[%s %s] %s:%d\n%s", __DATE__, __TIME__, __FILE__, __LINE__, __PRETTY_FUNCTION__ );

#ifndef NTRACE
#define TRACE DETAILS std::printf( "\n" );
#else
#define TRACE NOOP;
#endif

#define LOG_ERROR( fmt, ... ) DETAILS( stderr ) std::fprintf( stderr, "\n" COLOR_RED fmt COLOR_DEFAULT "\n", ##__VA_ARGS__ )

#ifndef NDEBUG
#define LOG_INFO( fmt, ... ) DETAILS( stdout ) std::printf( "\n" COLOR_YELLOW fmt COLOR_DEFAULT "\n", ##__VA_ARGS__ )
#else
#define LOG_INFO( fmt, ... ) NOOP
#endif
