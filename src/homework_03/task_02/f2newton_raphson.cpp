#include "../f2.hpp"

#include <caas/optimization/newton_raphson.hpp>
#include <caas/optimization/types.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 2 >;

    F2 f;
    auto result{ caas::optimization::newton_raphson( f, Point{ 0.1, 0.3 }, 0, 1e-7, true, 1 ) };

    std::cout << "Result: " << result << '\n';

    std::cout << "Function calls: " << f.functionCalls() << '\n';
    std::cout << "Gradient calls: " << f.gradientCalls() << '\n';
    std::cout << "Hessian  calls: " << f.hessianCalls () << '\n';

    return 0;
}