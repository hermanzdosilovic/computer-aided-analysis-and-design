#pragma once

#include <cmath>
#include <cstdint>

class F4
{
public:
    template< typename T >
    double operator()( T const & x )
    {
        ++functionCalls_;
        return std::pow( x[ 0 ] - 3, 2 ) + std::pow( x[ 1 ], 2 );
    }

    auto functionCalls() const { return functionCalls_; }

private:
    std::uint64_t functionCalls_{};
};