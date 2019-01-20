#pragma once

#include <caas/matrix.hpp>

#include <cmath>
#include <cstdint>

class F1
{
public:
    template< typename T >
    double operator()( T const & x )
    {
        ++functionCalls_;
        return 100 * std::pow( x[ 1 ] - std::pow( x[ 0 ], 2 ), 2 ) + std::pow( 1 - x[ 0 ], 2 );
    }

    template< typename T >
    auto gradient( T const & x )
    {
        ++gradientCalls_;

        auto result{ x };
        result[ 0 ] = -400 * x[ 0 ] * x[ 1 ] + 400 * std::pow( x[ 0 ], 3 ) + 2 * x[ 0 ] - 2;
        result[ 1 ] = 200 * x[ 1 ] - 200 * std::pow( x[ 0 ], 2 );

        return result;
    }

    template< typename T >
    auto hessian( T const & x )
    {
        ++hessianCalls_;

        caas::Matrix result{ 2, 2 };
        result( 0, 0 ) = -400 * x[ 1 ] + 1200 * std::pow( x[ 0 ], 2 ) + 2;
        result( 0, 1 ) = -400 * x[ 0 ];
        result( 1, 0 ) = -400 * x[ 0 ];
        result( 1, 1 ) = 200;

        return result;
    }

    auto functionCalls() const { return functionCalls_; }
    auto gradientCalls() const { return gradientCalls_; }
    auto hessianCalls () const { return hessianCalls_;  }

private:
    std::uint64_t functionCalls_{};
    std::uint64_t gradientCalls_{};
    std::uint64_t hessianCalls_{};
};