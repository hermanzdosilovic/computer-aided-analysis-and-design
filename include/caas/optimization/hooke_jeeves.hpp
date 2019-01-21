#pragma once

#include <caas/optimization/types.hpp>
#include <caas/utils/log.hpp>

namespace caas::optimization
{

template< typename Function, typename T >
T hooke_jeeves( Function f, T const & x0, T const & dx, T const & precision )
{
    #define ITERATION_LOG() \
    LOG_INFO \
    ( \
        "Iteration %u: f(xb=%s) = %f, f(xp=%s) = %f, f(xn=%s) = %f\n", \
        iteration, std::to_string( xb ).c_str(), f( xb ), std::to_string( xp ).c_str(), f( xp ), std::to_string( xn ).c_str(), f( xn ) \
    )

    auto const N{ std::size( x0 ) };

    T xp{ x0 };
    T xb{ x0 };
    T d{ dx };

    double fP{ f( xp ) };
    double fB{ fP }, fN{ fP };

    std::uint16_t iteration{ 0 };
    std::uint16_t functionCalls{ 1 };

    do
    {
        T xn{ xp };
        fN = fP;
        for ( std::size_t i{ 0 }; i < N; ++i )
        {
            xn[ i ] += d[ i ];
            double n{ f( xn ) };
            ++functionCalls;

            if ( n > fN )
            {
                xn[ i ] -= 2 * d[ i ];
                n = f( xn );
                ++functionCalls;
                if ( n > fN )
                {
                    xn[ i ] += d[ i ];
                }
                else
                {
                    fN = n;
                }
            }
            else
            {
                fN = n;
            }
        }

        ITERATION_LOG();

        if ( fN < fB )
        {
            xp = 2 * xn - xb;
            fP = f( xp );
            ++functionCalls;
            xb = xn;
            fB = fN;
        }
        else
        {
            d *= 0.5;
            xp = xb;
            fP = fB;
        }

        ++iteration;
    } while ( !( d <= precision ) );

    LOG_INFO( "Total number of function calls: %u\n", functionCalls );

    #undef ITERATION_LOG

    return xb;
}

}
