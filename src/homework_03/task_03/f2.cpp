#include "constrains.hpp"
#include "../f2.hpp"

#include <caas/optimization/box.hpp>
#include <caas/optimization/types.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 2 >;

    auto implicitConstrains{ getImplicitConstrains< Point >() };

    // Explicit constrains.
    Point lowerBound{ -100, -100 };
    Point upperBound{  100,  100 };

    F2 f;

    auto result{ caas::optimization::box( f, Point{ 0.1, 0.3 }, implicitConstrains, lowerBound, upperBound, 1.3, 1e-6 ) };

    std::cout << "Result: " << result << '\n';

    std::cout << "Function calls: " << f.functionCalls() << '\n';

    return 0;
}