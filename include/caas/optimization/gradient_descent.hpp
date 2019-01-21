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
    auto gradient{ f.gradient( x ) };
    auto i{ 0 };

    auto lastFunctionValue{ f( x ) };
    std::uint16_t converganceCounter{ 0 };

    for (; norm( gradient ) > precision; ++i )
    {
        auto const currentFunctionValue{ f( x ) };
        if ( std::abs( lastFunctionValue - currentFunctionValue ) < 1e-12 )
        {
            ++converganceCounter;
            if ( converganceCounter == 100 )
            {
                break;
            }
        }
        else
        {
            converganceCounter = 0;
        }

        lastFunctionValue = currentFunctionValue;

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
            std::cout << i << ") x = " << x << "; f(x) = " << lastFunctionValue << "; step = " << step << "; gradient = " << gradient << '\n';
        }

        x -= step * gradient;

        gradient = f.gradient( x );
    }

    if ( logFrequency > 0 )
    {
        lastFunctionValue = f( x );
        std::cout << i << ") x = " << x << "; f(x) = " << lastFunctionValue << "; step = " << step << "; gradient = " << gradient << '\n';
    }

    if ( converganceCounter == 100 )
    {
        std::cout << "Gradient descent method does not converge.\n";
    }

    return x;
}

}