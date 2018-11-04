#include <caas/optimization/simplex.hpp>
#include <caas/function.hpp>

#include <iostream>
#include <random>

int main()
{
    std::random_device randomDevice;
    std::mt19937 randomGenerator( randomDevice() );
    std::uniform_real_distribution distribution{ -50.0, 50.0 };

    for ( auto i{ 0 }; i < 10; ++i )
    {
        double x0{ distribution( randomGenerator ) }, x1{ distribution( randomGenerator ) };

        auto xm{ caas::optimization::simplex( caas::function::shafferf6< caas::Point< 2 > >, caas::Point< 2 >{ x0, x1 }, 1, 1e-4, 1, 0.5, 2, 0.5 ) };
        std::cout << "Solution: f1(" << xm << ") = " << caas::function::shafferf6( xm ) << '\n';
    }

    return 0;
}
