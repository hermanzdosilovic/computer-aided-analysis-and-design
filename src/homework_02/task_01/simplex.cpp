#include <caas/optimization/simplex.hpp>

#include <iostream>

int main()
{
    auto const f3{ []( caas::Point< 1 > const & x ){ return ( std::get< 0 >( x ) - 3 ) * ( std::get< 0 >( x ) - 3 ); } };

    double x0, distance, precision, alpha, beta, gamma, sigma;
    std::cin >> x0 >> distance >> precision >> alpha >> beta >> gamma >> sigma;

    auto xm{ caas::optimization::simplex( f3, caas::Point< 1 >{ x0 }, distance, precision, alpha, beta, gamma, sigma ) };
    std::cout << "Solution: f3(" << xm << ") = " << f3( xm ) << '\n';

    return 0;
}
