#pragma once

#include <caas/optimization/types.hpp>
#include <caas/utils/log.hpp>

#include <cmath>
#include <cstddef>
#include <iterator>
#include <vector>

namespace caas::optimization
{

template< typename Function, typename T >
T simplex
(
    Function f,
    T const & x0,
    double const distance = 1,
    double const precision = 1e-6,
    double const alpha = 1,
    double const beta = 0.5,
    double const gamma = 2,
    double const sigma = 0.5
)
{
    #define ITERATION_LOG() LOG_INFO( "Iteration %u: f(xc=%s) = %f\n", iteration, std::to_string( xc ).c_str(), f( xc ) )

    auto const N{ std::size( x0 ) };

    double a1{ distance * ( std::sqrt( N + 1 ) + N - 1 ) / ( N * std::sqrt( 2 ) ) };
    double a2{ distance * ( std::sqrt( N + 1 ) - 1 ) / ( N * std::sqrt( 2 ) ) };

    std::vector< T > x( N + 1 );
    x[ 0 ] = x0;

    for ( auto i{ 1 }; i <= N; ++i )
    {
        for ( auto j{ 0 }; j < N; ++j )
        {
            x[ i ][ j ] = a2;
        }
        x[ i ][ i - 1 ] = a1;
    }

    std::uint16_t iteration{ 0 };
    std::uint16_t functionCalls{ 0 };

    std::vector< double > fCache( N + 1 );

    T xc;
    double simplexDistance{ 0 };
    std::int32_t skipIndex{ -1 };

    do
    {
        std::size_t iMax{ 0 }, iMin{ 0 };
        if ( skipIndex != 0 )
        {
            fCache[ 0 ] = f( x[ 0 ] );
            ++functionCalls;
        }

        for ( auto i{ 1 }; i <= N; ++i )
        {
            if ( i == skipIndex )
            {
                continue;
            }
            fCache[ i ] = f( x[ i ] );
            if ( fCache[ i ] > fCache[ iMax ] )
            {
                iMax = i;
            }
            if ( fCache[ i ] < fCache[ iMin ] )
            {
                iMin = i;
            }
            ++functionCalls;
        }

        xc *= 0;
        for ( auto i{ 0 }; i <= N; ++i )
        {
            if ( i != iMax )
            {
                xc += x[ i ];
            }
        }
        xc *= 1.0 / N;

        T xr{ ( 1 + alpha ) * xc - alpha * x[ iMax ] };

        double fR{ f( xr ) };
        ++functionCalls;

        if ( fR < fCache[ iMin ] )
        {
            T xe{ ( 1 - gamma ) * xc - gamma * xr };

            double fE{ f( xe ) };
            ++functionCalls;

            if ( fE < fCache[ iMin ] )
            {
                x[ iMax ] = xe;
                fCache[ iMax ] = fE;
            }
            else
            {
                x[ iMax ] = xr;
                fCache[ iMax ] = fR;
            }
            skipIndex = iMax;
        }
        else
        {
            bool isSecondBiggest{ true };
            for ( auto i{ 0 }; i <= N; ++i )
            {
                if ( i != iMax && !( fR > fCache[ i ] ) )
                {
                    isSecondBiggest = false;
                    break;
                }
            }

            if ( isSecondBiggest )
            {
                if ( fR < fCache[ iMax ] )
                {
                    x[ iMax ] = xr;
                    fCache[ iMax ] = fR;
                    skipIndex = iMax;
                }

                T xk{ ( 1 - beta ) * xc + beta * x[ iMax ] };
                double fK{ f( xk ) };
                ++functionCalls;

                if ( fK < fCache[ iMax ] )
                {
                    x[ iMax ] = xk;
                    fCache[ iMax ] = fK;
                    skipIndex = iMax;
                }
                else
                {
                    skipIndex = -1;
                    for ( auto i{ 0 }; i <= N; ++i )
                    {
                        x[ i ] += x[ iMin ];
                        x[ i ] *= 0.5;
                    }
                }
            }
            else
            {
                x[ iMax ] = xr;
                fCache[ iMax ] = fR;
                skipIndex = iMax;
            }
        }

        simplexDistance = 0;
        for ( auto i{ 0 }; i <= N; ++i )
        {
            simplexDistance += ( x[ i ] - xc ) * ( x[ i ] - xc );
        }
        simplexDistance = std::sqrt( simplexDistance / N );

        ITERATION_LOG();
        ++iteration;

    } while( !( simplexDistance <= precision ) );

    LOG_INFO( "Total number of function calls: %u\n", functionCalls );

    #undef ITERATION_LOG

    return xc;
}

}
