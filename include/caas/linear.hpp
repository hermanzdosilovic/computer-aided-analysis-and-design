#pragma once

#include "lup.hpp"
#include "supstitution.hpp"

#include <cassert>
#include <utility>

namespace caas::linear
{

namespace internal
{

std::pair< Matrix, Matrix > separate( Matrix const & m )
{
    Matrix l{ Matrix::Identity( m.rows() ) };
    Matrix u{ m.rows() };
    for ( std::size_t i{ 0 }; i < m.rows(); ++i )
    {
        for ( std::size_t j{ 0 }; j < m.cols(); ++j )
        {
            if ( j >= i )
            {
                u( i, j ) = m( i, j );
            }
            else
            {
                l( i, j ) = m( i, j );
            }
        }
    }

    return { l, u };
}

}

Matrix solve( Matrix const & a, Matrix const & b )
{
    assert( a.rows() == a.cols() );
    assert( a.rows() == b.rows() && b.cols() == 1 );

    auto [ p, lu ] = decompose( a, Strategy::LUP );
    auto [ l, u ] = internal::separate( lu );

    auto y = supstitution::forward( l, p * b );
    auto x = supstitution::backward( u, y );

    return x;
}

}
