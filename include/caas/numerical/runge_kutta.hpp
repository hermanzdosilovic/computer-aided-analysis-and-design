#pragma once

#include <caas/matrix.hpp>
#include <caas/linear.hpp>

#include <cassert>
#include <vector>

namespace caas::numerical
{

auto runge_kutta( Matrix const & a, Matrix const & x0, double const step, double const tMax )
{
    assert( a.rows() == a .cols() );
    assert( a.cols() == x0.rows() );

    assert( step > 0    );
    assert( step < tMax );

    auto x{ x0 };

    std::vector< Matrix > states;
    states.reserve( tMax / step );

    for ( double t{ 0 }; t <= tMax; t += step )
    {
        states.emplace_back( x );

        auto const m1{ a * x };
        auto const m2{ a * ( x + m1 * step * 0.5 ) };
        auto const m3{ a * ( x + m2 * step * 0.5 ) };
        auto const m4{ a * ( x + m3 * step       ) };

        x += ( m1 + 2 * m2 + 2 * m3 + m4 ) * step / 6;
    }

    return states;
}

}
