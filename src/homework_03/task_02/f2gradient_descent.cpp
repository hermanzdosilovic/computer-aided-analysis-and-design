#include "../f2.hpp"

#include <caas/optimization/gradient_descent.hpp>
#include <caas/optimization/types.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 2 >;

    F2 f;
    auto result{ caas::optimization::gradient_descent( f, Point{ 0.1, 0.3 }, 0, 1e-5, true, 1 ) };

    std::cout << "Result: " << result << '\n';
    std::cout << "Function calls: " << f.functionCalls() << '\n';
    std::cout << "Gradient calls: " << f.gradientCalls() << '\n';

    return 0;
}