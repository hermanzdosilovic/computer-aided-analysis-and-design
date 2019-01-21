#pragma once

#include <caas/optimization/types.hpp>
#include <caas/utils/log.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

namespace caas::optimization
{

template< typename Function, typename T, typename ImplicitConstrains >
auto box
(
    Function && f,
    T const & x0,
    ImplicitConstrains const & implicitConstrains,
    T const & lowerBound,
    T const & upperBound,
    double const alpha = 1.3,
    double const precision = 1e-6
)
{
    auto const N{ std::size( x0 ) };

    for ( auto const & constrain : implicitConstrains )
    {
        if ( constrain( x0 ) < 0 )
        {
            std::cout << "Point x0 does not satisfy implicit constrains.\n";
            return x0;
        }
    }

    for ( auto i{ decltype( N ){ 0 } }; i < N; ++i )
    {
        if ( x0[ i ] < lowerBound[ i ] || x0[ i ] > upperBound[ i ] )
        {
            std::cout << "Point x0 does not satisfy explicit constrains.\n";
            return x0;
        }
    }

    std::mt19937 randomGenerator{ std::random_device{}() };
    std::uniform_real_distribution uniformDistribution( 0.0, 1.0 );

    std::vector< T > x( 2 * N );
    auto xc{ x0 };

    for ( std::size_t i{ 0 }; i < std::size( x ); ++i )
    {
        for ( auto j{ decltype( N ){ 0 } }; j < N; ++j )
        {
            x[ i ][ j ] = lowerBound[ j ] + uniformDistribution( randomGenerator ) * ( upperBound[ j ] - lowerBound[ j ] );
        }

        bool respectsImplicitConstrains{ false };
        while ( !respectsImplicitConstrains )
        {
            respectsImplicitConstrains = true;
            for ( auto const & constrain : implicitConstrains )
            {
                if ( constrain( x[ i ] ) < 0 )
                {
                    respectsImplicitConstrains = false;
                    break;
                }
            }

            if ( !respectsImplicitConstrains )
            {
                x[ i ]= 0.5 * ( x[ i ] + xc );
            }
        }

        xc *= 0;
        for ( auto const & e : x )
        {
            xc += e;
        }
        xc /= ( i + 1 );
    }

    double distance{ 0 };
    std::size_t i{ 0 };

    do
    {
        std::cout << i++ << ") xc = " << xc << "; f(xc) = " << f( xc ) << '\n';

        std::sort( std::begin( x ), std::end( x ), [ & f ]( auto const & a, auto const & b ){ return f( a ) < f( b ); } );
        auto h { std::size( x ) - 1 };
        auto h2{ std::size( x ) - 2 };

        xc *= 0;
        for ( auto i{ decltype( h ){ 0 } }; i < h; ++i )
        {
            xc += x[ i ];
        }
        xc /= h;

        auto xr{ ( 1 + alpha ) * xc - alpha * x[ h ] };
        for ( auto i{ decltype( N ){ 0 } }; i < N; ++i )
        {
            xr[ i ] = std::clamp( xr[ i ], lowerBound[ i ], upperBound[ i ] );
        }

        bool respectsImplicitConstrains{ false };
        while ( !respectsImplicitConstrains )
        {
            respectsImplicitConstrains = true;
            for ( auto const & constrain : implicitConstrains )
            {
                if ( constrain( xr ) < 0 )
                {
                    respectsImplicitConstrains = false;
                    break;
                }
            }

            if ( !respectsImplicitConstrains )
            {
                xr = 0.5 * ( xr + xc );
            }
        }

        if ( f( xr ) > f( x[ h2 ] ) )
        {
            xr = 0.5 * ( xr + xc );
        }

        x[ h ] = xr;

        distance = 0;
        for ( auto const & xi : x )
        {
            distance += ( xi - xc ) * ( xi - xc );
        }
        distance = std::sqrt( distance / std::size( x ) );

    } while( distance > precision );

    return xc;
}

}
