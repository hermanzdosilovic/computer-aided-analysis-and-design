#pragma once

#include <caas/optimization/golden.hpp>
#include <caas/linear.hpp>
#include <caas/matrix.hpp>

#include <cmath>
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
    auto getDirection
    {
        []( auto & f, auto const & x )
        {
            auto const hessian { linear::inverse( f.hessian( x ) ) };
            auto const gradient{ caas::Matrix::WithData( f.gradient( x ), std::size( x ), 1 ) };
            auto const hessianDotGradient{ hessian * gradient };

            auto const directionVector{ hessianDotGradient / norm( hessianDotGradient ) };

            auto direction{ x };

            std::generate
            (
                std::begin( direction ),
                std::end  ( direction ),
                [ it = std::begin( directionVector ), end = std::end( directionVector ) ]() mutable
                {
                    assert( it != end );
                    return *(it++);
                }
            );

            return direction;
        }
    };

    auto x{ x0 };

    for ( std::size_t i{ 0 }; ; ++i )
    {
        auto direction{ getDirection( f, x ) };

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

        direction *= step;

        if ( norm( direction ) < precision )
        {
            break;
        }

        x -= direction;
    }

    return x;
}

}