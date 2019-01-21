#include "../f4.hpp"

#include <caas/optimization/mixed_transformation.hpp>
#include <caas/optimization/types.hpp>

#include <functional>
#include <iostream>
#include <vector>

template< typename T >
auto getInequalityConstrains()
{
    using Function = std::function< double( T const & ) >;
    
    std::vector< Function > constrains;
    constrains.reserve( 2 );

    constrains.emplace_back( []( T const & x ){ return 3 - x[ 0 ] - x[ 1 ]; } );
    constrains.emplace_back( []( T const & x ){ return 3 + 1.5 * x[ 0 ] - x[ 1 ]; } );

    return constrains;
}

template< typename T >
auto getEqualityConstrains()
{
    using Function = std::function< double( T const & ) >;
    
    std::vector< Function > constrains;
    constrains.emplace_back( []( T const & x ){ return x[ 1 ] - 1; } );

    return constrains;
}

int main()
{
    using Point = caas::Point< 2 >;

    F4 f;
    auto const inequalityConstrains{ getInequalityConstrains< Point >() };
    auto const equalityConstrains  { getEqualityConstrains  < Point >() };

    auto const result{ caas::optimization::mixed_transformation( f, Point{ 0, 0 }, inequalityConstrains, equalityConstrains, 1e-7 ) };

    std::cout << "Result: " << result << '\n';
    std::cout << "Function calls: " << f.functionCalls() << '\n';

    return 0;
}