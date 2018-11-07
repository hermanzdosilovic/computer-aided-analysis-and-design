#pragma once

#include <caas/optimization/golden.hpp>
#include <caas/optimization/types.hpp>
#include <caas/utils/log.hpp>

#include <cstddef>
#include <iterator>
#include <vector>

namespace caas::optimization
{

template< typename Function, typename T >
T axis( Function f, T const & x0, T const & precision )
{
    #define ITERATION_LOG() LOG_INFO( "Iteration %u: f(%s) = %f\n", iteration, std::to_string( x ).c_str(), f( x ) )

    auto const N{ std::size( x0 ) };

    std::vector< T > e( N );
    for ( auto i{ 0 }; i < N; ++i )
    {
        e[ i ][ i ] = 1;
    }

    std::uint16_t iteration{ 0 };
    std::uint16_t functionCalls{ 0 };

    auto x{ x0 };
    T y;

    do
    {
        ITERATION_LOG();
        y = x;
        for ( auto i{ 0 }; i < N; ++i )
        {
            auto lambda = golden
            (
                [ & f, & x, & ei = e[ i ], & functionCalls ]( double const lambda )
                {
                    ++functionCalls;
                    return f( x + lambda * ei );
                },
                x[ i ],
                precision[ i ]
            );
            x += lambda * e[ i ];
            LOG_INFO( "Iteration %u: lambda[%d] = %f\n", iteration, i, lambda );
        }
        ++iteration;
    } while ( !( std::abs( x - y ) <= precision ) );

    ITERATION_LOG();
    LOG_INFO( "Total number of function calls: %u\n", functionCalls );

    #undef ITERATION_LOG

    return x;
}

}
