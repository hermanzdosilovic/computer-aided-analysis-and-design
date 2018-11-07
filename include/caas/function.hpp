#pragma once

#include <caas/optimization/types.hpp>

#include <cmath>
#include <cstdint>
#include <iterator>

namespace caas::function
{

template< typename T >
double series( T const & v )
{
    std::uint16_t i{ 1 };
    double result{ 0 };
    for ( auto const & x : v )
    {
        result += std::pow( x - i, 2 );
        ++i;
    }
    return result;
}

double rosenbrock( caas::Point< 2 > const & p )
{
    return 100 * std::pow( p[ 1 ] - std::pow( p[ 0 ], 2 ), 2 ) + std::pow( 1 - p[ 0 ], 2 );
}

double yeti( caas::Point< 2 > const & p )
{
    return std::abs( ( p[ 0 ] - p[ 1 ] ) * ( p[ 0 ] + p[ 1 ] ) ) + std::hypot( p[ 0 ], p[ 1 ] );
}

template< typename T >
double shafferf6( T const & p )
{
    double sum{ 0 };
    for ( auto const & i : p )
    {
        sum += i * i;
    }

    return 0.5 + ( std::pow( std::sin( sum ), 2 ) - 0.5 ) / std::pow( 1 + 0.001 * sum , 2);
}

}
