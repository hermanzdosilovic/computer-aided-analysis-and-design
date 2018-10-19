#pragma once

#include "matrix.hpp"

namespace caas::supstitution
{

void forward( Matrix const & matrix, Matrix & vector )
{
    assert( matrix.rows() == matrix.cols() );
    assert( vector.rows() == matrix.rows() && vector.cols() == 1 );

    for ( std::size_t i{ 0 }; i < vector.rows(); ++i )
    {
        vector( i, 0 ) = vector( i, 0 );
        for ( std::size_t j{ 0 }; j < i; ++j )
        {
            vector( i, 0 ) -= ( i == j ? 1 : ( i > j ? matrix( i, j ) : 0 ) )  * vector( j, 0 );
        }
    }
}

Matrix forward( Matrix const & matrix, Matrix const & vector )
{
    Matrix copy{ vector };
    forward( matrix, copy );
    return copy;
}

void backward( Matrix const & matrix, Matrix & vector )
{
    assert( matrix.rows() == matrix.cols() );
    assert( vector.rows() == matrix.rows() && vector.cols() == 1 );

    for ( std::size_t i{ vector.rows() - 1 }; i >= 0; --i )
    {
        vector( i, 0 ) = vector( i, 0 );
        for ( std::size_t j{ i + 1 }; j < vector.rows(); ++j )
        {
            vector( i, 0 ) -= ( j >= i ? matrix( i, j ) : 0 ) * vector( j, 0 );
        }
        vector( i, 0 ) /= matrix( i, i );

        if ( i == 0 )
        {
            break;
        }
    }
}

Matrix backward( Matrix const & matrix, Matrix const & vector )
{
    Matrix copy{ vector };
    backward( matrix, copy );
    return copy;
}

}
