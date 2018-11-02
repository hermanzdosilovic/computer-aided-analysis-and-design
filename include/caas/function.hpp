#pragma once

#include <cstdint>
#include <iterator>

namespace caas::function
{

template< typename InputIt >
double series( InputIt first, InputIt last )
{
    std::uint16_t i{ 1 };
    double result{ 0 };
    for ( ; first != last; ++first, ++i )
    {
        result += ( *first - i ) * ( *first - i );
    }
    return result;
}

template< typename T >
double series( T const & v )
{
    return series( std::begin( v ), std::end( v ) );
}

}
