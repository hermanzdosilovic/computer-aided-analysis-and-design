#pragma once

#include "golden.hpp"

#include <cstdint>
#include <iostream>

namespace caas::optimization
{

template< typename Function, typename T >
auto gradient_descent
( 
    Function && f, 
    T const & x0, 
    double step, 
    double const precision, 
    bool const useOptimalStep, 
    std::uint32_t const logFrequency = 0
)
{
    auto x{ x0 };
    for ( std::size_t i{ 0 }; ; ++i )
    {
        auto gradient{ f.gradient( x ) };

        if ( useOptimalStep )
        {
            step = golden
            (
                [ & f, & x, & gradient ]( double const lambda )
                {
                    return f( x - lambda * gradient );
                },
                0
            );
        }

        if ( logFrequency > 0 && i % logFrequency == 0 )
        {
            std::cout << i << ") x = " << x << "; step = " << step << "; gradient = " << gradient << '\n';
        }

        gradient *= step;

        if ( norm( gradient ) < precision )
        {
            break;
        }

        x -= gradient;
    }

    return x;
}

}