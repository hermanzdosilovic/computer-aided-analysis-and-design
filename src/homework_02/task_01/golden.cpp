#include <caas/optimization/golden.hpp>

#include <iostream>

int main()
{
    auto f3 = []( double const x ){ return ( x - 3 ) * ( x - 3 ); };

    double x0, step, precision;
    std::cin >> x0 >> step >> precision;

    auto xm = caas::optimization::golden( f3, x0, step, precision );
    std::cout << "Solution: f3(" << xm << ") = " << f3( xm ) << '\n';

    return 0;
}
