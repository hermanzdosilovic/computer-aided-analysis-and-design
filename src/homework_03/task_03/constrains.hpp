#pragma once

#include <functional>

template< typename T >
auto getImplicitConstrains()
{
    using Function = std::function< double( T const & ) >;
    
    std::vector< Function > constrains;
    constrains.reserve( 2 );

    constrains.emplace_back
    (
        []( T const & x )
        {
            return x[ 1 ] - x[ 0 ];
        }
    );

    constrains.emplace_back
    (
        []( T const & x )
        {
            return 2 - x[ 0 ];
        }
    );

    return constrains;
}