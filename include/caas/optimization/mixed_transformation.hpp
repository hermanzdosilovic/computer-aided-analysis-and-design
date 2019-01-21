#pragma once

#include "hooke_jeeves.hpp"

#include <cmath>
#include <cstdint>
#include <iostream>

namespace caas::optimization
{

template< typename Function, typename T, typename InequalityConstrains, typename EqualityConstrains >
auto mixed_transformation
(
    Function && f,
    T const & x0,
    InequalityConstrains const & inequalityConstrains,
    EqualityConstrains const & equalityConstrains,
    double const precision
)
{
    double t{ 10 };

    auto function 
    {
        [ & f, & inequalityConstrains, & equalityConstrains, & t ]( auto const & x )
        {
            auto const r{ 1 / t };
            auto result{ f( x ) };
            for ( auto const & g : inequalityConstrains )
            {
                result -= r * std::log( g( x ) );
            }
            for ( auto const & h : equalityConstrains )
            {
                result += t * std::pow( h( x ), 2 );
            }
            return result;
        }
    };

    auto x{ x0 };    
    auto y{ x0 };
    auto const dx{ 0.5 + 0 * x0 };
    auto const componentPrecision{ precision + 0 * x0 };

    for ( std::size_t i{ 0 }; ; ++i, t *= 10 )
    {
        std::cout << i << ") x = " << x << "; t = " << t << '\n';
        x = hooke_jeeves( function, y, dx, componentPrecision );

        if ( norm( x - y ) < precision )
        {
            break;
        }        

        y = x;
    }

    return x;
}

}