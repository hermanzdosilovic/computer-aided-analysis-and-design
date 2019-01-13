#pragma once

#include <caas/matrix.hpp>
#include <caas/linear.hpp>

#include <cassert>
#include <vector>

namespace caas::numerical
{

auto trapeze( Matrix const & a, Matrix const & x0, double const step, double const tMax )
{
    assert( a.rows() == a .cols() );
    assert( a.cols() == x0.rows() );

    assert( step > 0    );
    assert( step < tMax );

    auto const u{ Matrix{ a }.setIdentity() };
    auto const r{ linear::inverse( u - a * step * 0.5 ) * ( u + a * step * 0.5 ) };

    auto x{ x0 };

    std::vector< Matrix > states;
    states.reserve( tMax / step );

    for ( double t{ 0 }; t <= tMax; t += step )
    {
        states.emplace_back( x );
        x = r * x;
    }

    return states;
}

}
