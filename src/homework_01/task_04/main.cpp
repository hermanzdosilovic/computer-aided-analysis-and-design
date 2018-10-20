#include <caas/linear.hpp>

#include <iostream>

int main()
{
    caas::Matrix const a{ "test_data/hw01/matrix1_t04.txt" };
    caas::Matrix const b{ "test_data/hw01/vector1_t04.txt" };
    auto x1 = caas::linear::solve( a, b, caas::Strategy::LU );
    auto x2 = caas::linear::solve( a, b, caas::Strategy::LUP );
    std::cout << "x1:\n" << x1 << "\nx2:\n" << x1 << '\n';

    return 0;
}
