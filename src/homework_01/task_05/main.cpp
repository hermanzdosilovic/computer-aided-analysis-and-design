#include <caas/linear.hpp>

#include <iostream>

int main()
{
    caas::Matrix a{ "test_data/hw01/matrix1_t05.txt" };
    caas::Matrix b{ "test_data/hw01/vector1_t05.txt" };
    caas::linear::solve( a, b, caas::Strategy::LUP );
    std::cout << "x:\n" << b << '\n';

    return 0;
}
