#pragma once

#include "matrix.hpp"

namespace caas::supstitution
{

Matrix forward( Matrix const & matrix, Matrix const & vector )
{
    assert( matrix.rows() == matrix.cols() );
    assert( vector.rows() == matrix.rows() && vector.cols() == 1 );

#ifndef NDEBUG
    for ( std::size_t i{ 0 }; i < matrix.rows(); ++i )
    {
        for ( std::size_t j{ 0 }; j < matrix.cols(); ++j )
        {
            if ( i == j )
            {
                assert( matrix( i, j ) == 1 );
            }
            else if ( j > i )
            {
                assert( matrix( i, j ) == 0 );
            }
        }
    }
#endif

    Matrix result{ matrix.rows(), 1 };
    for ( std::size_t i{ 0 }; i < result.rows(); ++i )
    {
        result( i, 0 ) = vector( i, 0 );
        for ( std::size_t j{ 0 }; j < i; ++j )
        {
            result( i, 0 ) -= matrix( i, j ) * result( j, 0 );
        }
    }

    return result;
}

Matrix backward( Matrix const & matrix, Matrix const & vector )
{
    assert( matrix.rows() == matrix.cols() );
    assert( vector.rows() == matrix.rows() && vector.cols() == 1 );

#ifndef NDEBUG
    for ( std::size_t i{ 0 }; i < matrix.rows(); ++i )
    {
        for ( std::size_t j{ 0 }; j < matrix.cols(); ++j )
        {
            if ( i > j )
            {
                assert( matrix( i, j ) == 0 );
            }
        }
    }
#endif

    Matrix result{ matrix.rows(), 1 };
    for ( std::size_t i{ result.rows() - 1 }; i >= 0; --i )
    {
        result( i, 0 ) = vector( i, 0 );
        for ( std::size_t j{ i + 1 }; j < result.rows(); ++j )
        {
            result( i, 0 ) -= matrix( i, j ) * result( j, 0 );
        }
        result( i, 0 ) /= matrix( i, i );

        if ( i == 0 )
        {
            break;
        }
    }

    return result;
}

}
