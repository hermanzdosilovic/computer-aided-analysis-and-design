#include <caas/matrix.hpp>
#include <Eigen/Dense>

#include <iostream>
#include <iterator>

int main()
{
    caas::Matrix a{ caas::Matrix::Random( 2, 3 ) };
    a( 0, 0 ) = 6;
    std::cout << a << std::endl;
    return 0;
}
