#pragma once

#include "matrix.hpp"
#include "utils/log.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <utility>

#ifndef NDEBUG
#include <iostream>
#endif

namespace caas
{

enum class Strategy : std::uint8_t
{
    LU,
    LUP
};

void decompose( Matrix & matrix, Matrix & vector, Strategy const strategy = Strategy::LUP, double const precision = 1e-5 )
{
    assert( matrix.rows() == matrix.cols() );
    assert( matrix.rows() == vector.rows() );

    for ( std::size_t i{ 0 }; i < matrix.rows() - 1; ++i )
    {
        if ( std::abs( matrix( i, i ) ) < precision )
        {
            if ( strategy == Strategy::LU )
            {
                LOG_ERROR( "Pivot element at position (%d, %d) is %f.", i, i, matrix(i, i) );
                LOG_ERROR( "Use LUP decomposition instead of LU decomposition." );
                break;
            }

            auto maxAbsPivot{ std::abs( matrix( i, i ) ) };
            std::size_t index{ i };
            for ( std::size_t j{ i + 1 }; j < matrix.rows(); ++j )
            {
                if ( maxAbsPivot < std::abs( matrix( j, i ) ) )
                {
                    maxAbsPivot = std::abs( matrix( j, i ) );
                    index = j;
                }
            }

            if ( maxAbsPivot < precision )
            {
                LOG_ERROR( "Found maximum absolute pivot at position (%d, %d) with value %f.", index, i, matrix( index, i ) );
                break;
            }

            matrix.swapRows( index, i );
            vector.swapRows( index, i );
        }

        for ( std::size_t j{ i + 1 }; j < matrix.cols(); ++j )
        {
            matrix( j, i ) /= matrix( i, i );
            for ( std::size_t k{ i + 1 }; k < matrix.cols(); ++k )
            {
                matrix( j, k ) -= matrix( j, i ) * matrix( i, k );
            }
        }

    #ifndef NDEBUG
        std::cout << matrix << '\n';
    #endif

    }
}

auto decompose( Matrix const & matrix, Strategy const strategy = Strategy::LUP, double const precision = 1e-5 )
{
    Matrix copy{ matrix };
    Matrix permutationMatrix = Matrix::Identity( copy.rows() );
    decompose( copy, permutationMatrix, strategy, precision );
    return std::pair{ permutationMatrix, copy };
}

}
