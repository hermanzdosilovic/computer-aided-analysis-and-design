#include "constrains.hpp"
#include "../f1.hpp"

#include <caas/optimization/mixed_transformation.hpp>
#include <caas/optimization/types.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 2 >;

    F1 f;
    auto const inequalityConstrains{ getInequalityConstrains< Point >() };
    auto const equalityConstrains  { getEqualityConstrains  < Point >() };

    auto const result{ caas::optimization::mixed_transformation( f, Point{ -1.9, 2 }, inequalityConstrains, equalityConstrains, 1e-7 ) };

    std::cout << "Result: " << result << '\n';
    std::cout << "Function calls: " << f.functionCalls() << '\n';

    return 0;
}