#pragma once

#include <caas/optimization/golden.hpp>
#include <caas/linear.hpp>
#include <caas/matrix.hpp>

#include <cstdint>
#include <iostream>
#include <iterator>

namespace caas::optimization
{

template< typename Function, typename T >
auto newton_raphson
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
    auto gradient{ caas::Matrix::WithData( f.gradient( x ), std::size( x ), 1 ) };
    auto hessian{ linear::inverse( f.hessian( x ) ) };
    
    auto getDirection
    {
        [ & x ]( auto const & gradient, auto const & hessian )
        {
            auto const directionVector{ ( hessian * gradient ) };
            auto direction{ x };

            std::size_t i{ 0 };
            for ( auto const v : directionVector )
            {
                direction[ i++ ] = v;
            }

            return direction;
        }
    };

    auto direction{ getDirection( gradient, hessian ) };

    auto i{ 0 };
    for (; norm( direction ) > precision; ++i )
    {
        if ( useOptimalStep )
        {
            step = golden
            (
                [ & f, & x, & direction ]( double const lambda )
                {
                    return f( x - lambda * direction );
                },
                0
            );
        }

        if ( logFrequency > 0 && i % logFrequency == 0 )
        {
            std::cout << i << ") x = " << x << "; step = " << step << "; direction = " << direction << '\n';
        }

        x -= step * direction;

        gradient = caas::Matrix::WithData( f.gradient( x ), std::size( x ), 1 );
        hessian = linear::inverse( f.hessian( x ) );
        direction = getDirection( gradient, hessian );
    }

    if ( logFrequency > 0 )
    {
        std::cout << i << ") x = " << x << "; step = " << step << "; direction = " << direction << '\n';
    }

    return x;
}

}