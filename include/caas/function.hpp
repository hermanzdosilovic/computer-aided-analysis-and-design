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
    return 100 * std::pow( std::get< 1 >( p ) - std::pow( std::get< 0 >( p ), 2 ), 2 ) + std::pow( 1 - std::get< 0 >( p ), 2 );
}

double yeti( caas::Point< 2 > const & p )
{
    auto const & x1{ std::get< 0 >( p ) };
    auto const & x2{ std::get< 1 >( p ) };
    return std::abs( ( x1 - x2 ) * ( x1 + x2 ) ) + std::hypot( x1, x2 );
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
