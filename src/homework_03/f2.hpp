#pragma once

#include <caas/matrix.hpp>

#include <cmath>
#include <cstdint>

class F2
{
public:
    template< typename T >
    double operator()( T const & x )
    {
        ++functionCalls_;
        return std::pow( x[ 0 ] - 4, 2 ) + 4 * std::pow( x[ 1 ] - 2, 2 );
    }

    template< typename T >
    auto gradient( T const & x )
    {
        ++gradientCalls_;

        auto result{ x };
        result[ 0 ] = 2 * ( x[ 0 ] - 4 );
        result[ 1 ] = 8 * ( x[ 1 ] - 2 );

        return result;
    }

    template< typename T >
    auto hessian( T const & )
    {
        ++hessianCalls_;

        caas::Matrix result{ 2, 2 };
        result( 0, 0 ) = 2;
        result( 0, 1 ) = 0;
        result( 1, 0 ) = 8;
        result( 1, 1 ) = 0;

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