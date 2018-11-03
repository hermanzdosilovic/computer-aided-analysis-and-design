#include <caas/optimization/hooke_jeeves.hpp>

#include <iostream>

int main()
{
    auto const f3{ []( caas::Point< 1 > const & x ){ return ( std::get< 0 >( x ) - 3 ) * ( std::get< 0 >( x ) - 3 ); } };

    double x0, dx, precision;
    std::cin >> x0 >> dx >> precision;

    auto xm{ caas::optimization::hooke_jeeves( f3, caas::Point< 1 >{ x0 }, caas::Point< 1 >{ dx }, caas::Point< 1 >{ precision } ) };
    std::cout << "Solution: f3(" << xm << ") = " << f3( xm ) << '\n';

    return 0;
}
