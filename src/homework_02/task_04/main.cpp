#include <caas/function.hpp>
#include <caas/optimization/simplex.hpp>

#include <iostream>

int main()
{
    double x0, distance, precision, alpha, beta, gamma, sigma;
    std::cin >> x0 >> distance >> precision >> alpha >> beta >> gamma >> sigma;

    auto xm{ caas::optimization::simplex( caas::function::rosenbrock, caas::Point< 2 >{ x0, x0 }, distance, precision, alpha, beta, gamma, sigma ) };
    std::cout << "Solution: f1(" << xm << ") = " << caas::function::rosenbrock( xm ) << '\n';

    return 0;
}
