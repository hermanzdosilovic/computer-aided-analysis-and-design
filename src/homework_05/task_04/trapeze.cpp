#include <caas/numerical/trapeze.hpp>

#include <sciplot/sciplot.hpp>

#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

int main()
{
    caas::Matrix a { "test_data/hw05/matrix1_t04.txt" };
    caas::Matrix x0{ "test_data/hw05/matrix2_t04.txt" };
    caas::Matrix b { "test_data/hw05/matrix3_t04.txt" };

    auto step{ 0.1 };
    auto tMax{ 10 };

    auto states{ caas::numerical::trapeze( a, x0, b, step, tMax ) };

    std::vector< double > x( std::size( states ) );
    std::vector< double > elongation( std::size( states ) );
    std::vector< double > speed( std::size( states ) );

    std::size_t i{ 0 };
    for ( double t{ 0 }; t < tMax; t += step )
    {
        x[ i ] = t;

        elongation[ i ] = states[ i ]( 0, 0 );
        speed[ i ] = states[ i ]( 1, 0 );

        std::cout << "t = " << t <<
                     "; elongation = " << elongation[ i ] <<
                     "; speed = " << speed[ i ] << '\n';

        ++i;
    }

    sciplot::plot plot;
    plot.draw( x, elongation ).title("elongation");
    plot.draw( x, speed      ).title("speed");
    plot.show();

    return 0;
}
