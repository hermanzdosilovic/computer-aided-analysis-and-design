#pragma once

#include "matrix.hpp"

#include <cassert>

namespace caas
{

Matrix forwardSupstitution( Matrix const & matrix, Matrix const & vector )
{
    assert( matrix.rows() == matrix.cols() );
    assert( vector.rows() == matrix.rows() && vector.cols() == 1 );

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

    Matrix result{ matrix.rows(), 1 };
    for ( std::size_t i{ 0 }; i < result.rows(); ++i )
    {
        result( i, 1 ) = vector( i, 1 );
        for ( std::size_t j{ 0 }; j < i; ++j )
        {
            result( i, 1 ) -= matrix( i, j ) * result( j, 1 );
        }
    }

    return result;
}

Matrix backwardSupstitution( Matrix const & matrix, Matrix const & vector )
{
    assert( matrix.rows() == matrix.cols() );
    assert( vector.rows() == matrix.rows() && vector.cols() == 1 );

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

    Matrix result{ matrix.rows(), 1 };
    for ( std::size_t i{ result.rows() - 1 }; i >= 0; --i )
    {
        result( i, 1 ) = vector( i, 1 );
        for ( std::size_t j{ i + 1 }; j < result.rows(); j++ )
        {
            result( i, 1 ) -= matrix( i, j ) * result( j, 1 );
        }
        result( i, 1 ) /= matrix( i, i );
    }

    return result;
}

Matrix decompose( Matrix const & matrix )
{
    assert( matrix.rows() == matrix.cols() );

    Matrix result{ matrix };
    for ( std::size_t i{ 0 }; i < result.rows() - 1; ++i )
    {
        for ( std::size_t j{ i + 1 }; j < result.cols(); ++j )
        {
            result( j, i ) /= result( i, i );
            for ( std::size_t k{ i + 1 }; k < result.cols(); ++k )
            {
                result( j, k ) -= result( j, i ) * result( i, k );
            }
        }
    }

    return result;
}

}
