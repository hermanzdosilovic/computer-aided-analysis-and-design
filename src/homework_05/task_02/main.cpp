#include <caas/linear.hpp>
#include <caas/matrix.hpp>

#include <iostream>

int main()
{
    caas::Matrix m{ "test_data/hw05/matrix1_t02.txt" };
    auto mInverse{ caas::linear::inverse( m ) };

    std::cout << mInverse << '\n';

    return 0;
}
