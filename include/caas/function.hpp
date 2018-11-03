#pragma once

#include <caas/optimization/types.hpp>

#include <cmath>
#include <cstdint>
#include <iterator>

namespace caas::function
{

namespace internal {
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
}

template< typename T >
double series( T const & v )
{
    return internal::series( std::begin( v ), std::end( v ) );
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
}
