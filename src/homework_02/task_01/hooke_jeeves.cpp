#include <caas/optimization/hooke_jeeves.hpp>

#include <iostream>

int main()
{
    using Point = caas::Point< 1 >;

    auto const f3{ []( Point const & x ){ return std::pow( x[ 0 ] - 3, 2 ); } };

    double x0, dx, precision;
    std::cin >> x0 >> dx >> precision;

    auto xm{ caas::optimization::hooke_jeeves( f3, Point{ x0 }, caas::Point< 1 >{ dx }, caas::Point< 1 >{ precision } ) };
    std::cout << "Solution: f3(" << xm << ") = " << f3( xm ) << '\n';

    return 0;
}
