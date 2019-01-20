#include "../f3.hpp"

#include <caas/optimization/gradient_descent.hpp>
#include <caas/optimization/types.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 2 >;

    auto result1{ caas::optimization::gradient_descent( F3{}, caas::Point< 2 >{ 0, 0 }, 1e-2, 1e-7, false, 1 ) };
    auto result2{ caas::optimization::gradient_descent( F3{}, caas::Point< 2 >{ 0, 0 }, 1e-3, 1e-7, true, 1 ) };

    std::cout << result1 << '\n';
    std::cout << result2 << '\n';

    return 0;
}