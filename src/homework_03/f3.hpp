#pragma once

#include <cmath>

class F3
{
public:
    template< typename T >
    double operator()( T const & x ) const 
    {
        return std::pow( x[ 0 ] - 2, 2 ) + std::pow( x[ 1 ] + 3, 2 );
    }

    template< typename T >
    auto gradient( T const & x ) const 
    {
        auto result{ x };
        result[ 0 ] = 2 * ( x[ 0 ] - 2 );
        result[ 1 ] = 2 * ( x[ 1 ] + 3 );
        return result;
    }

};