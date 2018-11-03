#include <caas/function.hpp>
#include <caas/optimization/axis.hpp>
#include <caas/optimization/hooke_jeeves.hpp>
#include <caas/optimization/simplex.hpp>

#include <cmath>
#include <iostream>

int main()
{
    {
        caas::Point< 2 > x0{ -1.9, 2 };
        caas::Point< 2 > dx{ 0.5, 0.5 }, precision{ 1e-6, 1e-6 };

        auto xSimplex{ caas::optimization::simplex( caas::function::rosenbrock, x0 ) };
        std::cout << "Simplex solution for f1: f1(" << xSimplex << ") = " << caas::function::rosenbrock( xSimplex ) << '\n';

        auto xHookeJeeves{ caas::optimization::hooke_jeeves( caas::function::rosenbrock, x0, dx, precision ) };
        std::cout << "Hooke-Jeeves solution for f1: f1(" << xHookeJeeves << ") = " << caas::function::rosenbrock( xHookeJeeves ) << '\n';

        auto xAxis{ caas::optimization::axis( caas::function::rosenbrock, x0, precision ) };
        std::cout << "Axis solution for f1: f1(" << xAxis << ") = " << caas::function::rosenbrock( xAxis ) << '\n';
    }

    {
        auto const f2
        {
            []( caas::Point< 2 > const & p )
            {
                return std::pow( std::get< 0 >( p ) - 4, 2 ) + 4 * std::pow( std::get< 1 >( p ) - 2, 2 );
            }
        };

        caas::Point< 2 > x0{ 0.1, 0.3 };
        caas::Point< 2 > dx{ 0.5, 0.5 }, precision{ 1e-6, 1e-6 };

        auto xSimplex{ caas::optimization::simplex( f2, x0 ) };
        std::cout << "Simplex solution for f2: f2(" << xSimplex << ") = " << f2( xSimplex ) << '\n';

        auto xHookeJeeves{ caas::optimization::hooke_jeeves( f2, x0, dx, precision ) };
        std::cout << "Hooke-Jeeves solution for f2: f2(" << xHookeJeeves << ") = " << f2( xHookeJeeves ) << '\n';

        auto xAxis{ caas::optimization::axis( f2, x0, precision ) };
        std::cout << "Axis solution for f2: f2(" << xAxis << ") = " << f2( xAxis ) << '\n';
    }

    {
        caas::Point< 5 > x0{ 0, 0, 0, 0, 0 };
        caas::Point< 5 > dx{ 0.5, 0.5, 0.5, 0.5, 0.5 }, precision{ 1e-6, 1e-6, 1e-6, 1e-6, 1e-6 };

        auto xSimplex{ caas::optimization::simplex( caas::function::series< caas::Point< 5 > >, x0 ) };
        std::cout << "Simplex solution for f3: f3(" << xSimplex << ") = " << caas::function::series( xSimplex ) << '\n';

        auto xHookeJeeves{ caas::optimization::hooke_jeeves( caas::function::series< caas::Point< 5 > >, x0, dx, precision ) };
        std::cout << "Hooke-Jeeves solution for f3: f3(" << xHookeJeeves << ") = " << caas::function::series( xHookeJeeves ) << '\n';

        auto xAxis{ caas::optimization::axis( caas::function::series< caas::Point< 5 > >, x0, precision ) };
        std::cout << "Axis solution for f3: f3(" << xAxis << ") = " << caas::function::series( xAxis ) << '\n';
    }

    {
        caas::Point< 2 > x0{ 5.1, 1.1 };
        caas::Point< 2 > dx{ 0.5, 0.5 }, precision{ 1e-6, 1e-6 };

        auto xSimplex{ caas::optimization::simplex( caas::function::yeti, x0 ) };
        std::cout << "Simplex solution for f4: f4(" << xSimplex << ") = " << caas::function::yeti( xSimplex ) << '\n';

        auto xHookeJeeves{ caas::optimization::hooke_jeeves( caas::function::yeti, x0, dx, precision ) };
        std::cout << "Hooke-Jeeves solution for f4: f4(" << xHookeJeeves << ") = " << caas::function::yeti( xHookeJeeves ) << '\n';

        auto xAxis{ caas::optimization::axis( caas::function::yeti, x0, precision ) };
        std::cout << "Axis solution for f4: f4(" << xAxis << ") = " << caas::function::yeti( xAxis ) << '\n';
    }

    return 0;
}
