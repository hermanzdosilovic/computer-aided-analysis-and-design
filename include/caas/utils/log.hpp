#pragma once

#include <cstdio>

#define N0OP ( ( void ) 0 )
#define DETAILS( file ) std::fprintf( file, "[%s %s] %s:%d %s", __DATE__, __TIME__, __FILE__, __LINE__, __PRETTY_FUNCTION__ );

#ifndef NTRACE
#define TRACE DETAILS std::printf( "\n" );
#else
#define TRACE N0OP;
#endif

#define LOG_ERROR( fmt, ... ) DETAILS( stderr ) std::fprintf( stderr, ": " fmt "\n", ##__VA_ARGS__ )

#ifndef NDEBUG
#define LOG_INFO( fmt, ... ) DETAILS( stdout ) std::printf( ": " fmt "\n", ##__VA_ARGS__ )
#else
#define LOG_INFO( fmt, ... ) NO0P
#endif
