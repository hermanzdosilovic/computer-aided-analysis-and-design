#pragma once

#include "lup.hpp"
#include "supstitution.hpp"
#include "utils/log.hpp"

#include <cassert>
#include <utility>
#include <vector>

namespace caas::linear
{

void solve( Matrix & a, Matrix & b, Strategy const strategy = Strategy::LUP, double const precision = 1e-5 )
{
    assert( a.rows() == a.cols() );
    assert( a.rows() == b.rows() && b.cols() == 1 );

    decompose( a, b, strategy, precision );

    supstitution::forward( a, b );
    supstitution::backward( a, b );
}

Matrix solve( Matrix const & a, Matrix const & b, Strategy const strategy = Strategy::LUP, double const precision = 1e-5 )
{
    Matrix c{ a }, d{ b };
    solve( c, d, strategy, precision );
    return d;
}

Matrix inverse( Matrix const & matrix )
{
    assert( matrix.rows() == matrix.cols() );

    auto [ p, lu ] = decompose( matrix, Strategy::LUP );

    std::vector< Matrix > xSolutions;
    xSolutions.reserve( lu.rows() );

    for ( std::size_t i{ 0 }; i < lu.rows(); ++i )
    {
        Matrix m{ lu.rows(), 1 };
        m( i, 0 ) = 1;
        m = p * m;
        supstitution::forward( lu, m );
        supstitution::backward( lu, m );
        xSolutions.emplace_back( m );
    }

    for ( std::size_t i{ 0 }; i < lu.rows(); ++i )
    {
        for ( std::size_t j{ 0 }; j < lu.cols(); ++j )
        {
            lu( i, j ) = xSolutions[ j ]( i, 0 );
        }
    }

    Matrix identity{ Matrix::Identity( lu.rows() ) };
    if ( lu.hasNan() || lu.hasInf() )
    {
        LOG_ERROR( "Matirx does not have inverse." );
    }

    return lu;
}

}
