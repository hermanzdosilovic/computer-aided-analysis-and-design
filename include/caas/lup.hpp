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

std::pair< Matrix, Matrix > decompose( Matrix const & matrix, Strategy const strategy = Strategy::LUP, double const precision = 1e-5 )
{
    assert( matrix.rows() == matrix.cols() );

    Matrix result{ matrix };
    Matrix permutationMatrix{ Matrix::Identity( matrix.rows() ) };
    bool decomposeError{ false };

    for ( std::size_t i{ 0 }; i < result.rows() - 1; ++i )
    {
        if ( std::abs( result( i, i ) ) < precision )
        {
            if ( strategy == Strategy::LU )
            {
                LOG_ERROR( "Pivot element at position (%d, %d) is %f.", i, i, result(i, i) );
                LOG_ERROR( "Use LUP decomposition instead of LU decomposition." );
                decomposeError = true;
                break;
            }

            double maxAbsPivot{ std::abs( result( i, i ) ) };
            std::size_t index{ i };
            for ( std::size_t j{ i + 1 }; j < result.rows(); ++j )
            {
                if ( maxAbsPivot < std::abs( result( j, i ) ) )
                {
                    maxAbsPivot = std::abs( result( j, i ) );
                    index = j;
                }
            }

            if ( maxAbsPivot < precision )
            {
                LOG_ERROR( "Found maximum absolute pivot at position (%d, %d) with value %f.", index, i, result( index, i ) );
                decomposeError = true;
                break;
            }

            result.swapRows( index, i );
            permutationMatrix.swapRows( index, i );
        }

        for ( std::size_t j{ i + 1 }; j < result.cols(); ++j )
        {
            result( j, i ) /= result( i, i );
            for ( std::size_t k{ i + 1 }; k < result.cols(); ++k )
            {
                result( j, k ) -= result( j, i ) * result( i, k );
            }
        }

    #ifndef NDEBUG
        std::cout << result << '\n';
    #endif

    }

    if ( decomposeError )
    {
        LOG_ERROR( "Decomposition failed." );
        result = matrix;
        permutationMatrix.setIdentity();
    }

    return { permutationMatrix, result };
}

}
