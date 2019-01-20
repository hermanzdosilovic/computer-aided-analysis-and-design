#include "../f1.hpp"

#include <caas/optimization/gradient_descent.hpp>
#include <caas/optimization/types.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 2 >;

    F1 f;
    auto result{ caas::optimization::gradient_descent( f, Point{ -1.9, 2 }, 1e-3, 1e-7, true, 1000 ) };

    std::cout << "Result: " << result << '\n';
    std::cout << "Function calls: " << f.functionCalls() << '\n';
    std::cout << "Gradient calls: " << f.gradientCalls() << '\n';

    return 0;
}