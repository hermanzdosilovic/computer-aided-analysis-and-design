#include <caas/function.hpp>
#include <caas/optimization/hooke_jeeves.hpp>
#include <caas/optimization/simplex.hpp>

#include <iostream>

int main()
{
    caas::Point< 2 > x0{ 5, 5 };
    caas::Point< 2 > dx{ 0.5, 0.5 }, precision{ 1e-6, 1e-6 };

    auto xSimplex{ caas::optimization::simplex( caas::function::yeti, x0 ) };
    std::cout << "Simplex solution for f4: f4(" << xSimplex << ") = " << caas::function::yeti( xSimplex ) << '\n';

    auto xHookeJeeves{ caas::optimization::hooke_jeeves( caas::function::yeti, x0, dx, precision ) };
    std::cout << "Hooke-Jeeves solution for f4: f4(" << xHookeJeeves << ") = " << caas::function::yeti( xHookeJeeves ) << '\n';

    return 0;
}
