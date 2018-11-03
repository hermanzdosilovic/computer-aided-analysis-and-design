#pragma once

#include <caas/utils/log.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <utility>

namespace caas::optimization
{

constexpr double kGoldenRatio{ 1.6180339887498948482045868343656381177203091798057628621 };
constexpr double kIntervalRatio{ kGoldenRatio - 1 };

template< typename Function >
std::pair< double, double > unimodal_interval( Function f, double const x0, double const step )
{
    #define ITERATION_LOG() LOG_INFO( "Iteration %u: f(left=%f) = %f, f(middle=%f) = %f, f(right=%f) = %f\n", iteration, left, fLeft, middle, fMiddle, right, fRight )

    double left{ x0 - step };
    double right{ x0 + step };
    double middle{ x0 };

    double fLeft{ f( left ) };
    double fRight{ f( right ) };
    double fMiddle{ f( middle ) };

    std::uint16_t iteration{ 0 };
    std::uint16_t functionCalls{ 3 };
    std::uint16_t powerOfTwo{ 1 };

    ITERATION_LOG();

    if ( fMiddle > fRight )
    {
        do
        {
            left = middle;
            middle = right;
            fLeft = fMiddle;
            fMiddle = fRight;
            right = x0 + step * ( powerOfTwo *= 2 );
            fRight = f( right );
            ++functionCalls;
            ++iteration;
            ITERATION_LOG();
        } while ( fMiddle > fRight );
    }
    else if ( fMiddle > fLeft )
    {
        do
        {
            right = middle;
            middle = left;
            fRight = fMiddle;
            fMiddle = fLeft;
            left = x0 - step * ( powerOfTwo *= 2 );
            fLeft = f( left );
            ++functionCalls;
            ++iteration;
            ITERATION_LOG();
        } while ( fMiddle > fLeft );
    }

    LOG_INFO( "Total number of function calls: %u\n", functionCalls );

    #undef ITERATION_LOG

    return { left, right };
}

template< typename Function >
double golden( Function f, std::pair< double, double > const & interval, double const precision = 1e-6 )
{
    #define ITERATION_LOG() LOG_INFO( "Iteration %u: [%f, %f, %f, %f] f(%f) = %f, f(%f) = %f\n", iteration, left, middleLeft, middleRight, right, middleLeft, fMiddleLeft, middleRight, fMiddleRight )

    double left{ std::min( interval.first, interval.second ) };
    double right{ std::max( interval.first, interval.second ) };

    double middleLeft{ right - kIntervalRatio * std::abs( right - left ) };
    double middleRight{ left + kIntervalRatio * std::abs( right - left ) };

    double fMiddleLeft{ f( middleLeft ) };
    double fMiddleRight{ f( middleRight ) };

    std::uint16_t iteration{ 0 };
    std::uint16_t functionCalls{ 2 };

    ITERATION_LOG();

    while( std::abs( right - left ) > precision )
    {
        if ( fMiddleLeft < fMiddleRight )
        {
            right = middleRight;
            middleRight = middleLeft;
            middleLeft = right - kIntervalRatio * std::abs( right - left );
            fMiddleRight = fMiddleLeft;
            fMiddleLeft = f( middleLeft );
        }
        else
        {
            left = middleLeft;
            middleLeft = middleRight;
            middleRight = left + kIntervalRatio * std::abs( right - left );
            fMiddleLeft = fMiddleRight;
            fMiddleRight = f( middleRight );
        }
        ++functionCalls;
        ++iteration;
        ITERATION_LOG();
    }

    LOG_INFO( "Total number of function calls: %u\n", functionCalls );

    #undef ITERATION_LOG

    return ( left + right ) / 2;
}

template< typename Function >
double golden( Function f, double const x0, double const precision = 1e-6, double const step = 0.1 )
{
    return golden( f, unimodal_interval( f, x0 , step ), precision );
}

}
