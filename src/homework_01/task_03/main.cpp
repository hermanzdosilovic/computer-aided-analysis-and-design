#include <caas/linear.hpp>
#include <caas/lup.hpp>

#include <iostream>

int main()
{
    caas::Matrix m1{ "test_data/hw01/matrix1_t02.txt" };
    auto m1Inverse = caas::linear::inverse( m1 );
    std::cout << "m1Inverse:\n" << m1Inverse << "\nm1 * m1Inverse:\n" << m1 * m1Inverse << '\n';

    caas::Matrix m2{ "test_data/hw01/matrix1_t03.txt" };
    auto const [ p, lu ] = caas::decompose( m2, caas::Strategy::LUP );
    std::cout << "p:\n" << p << "\nlu:\n" << lu << '\n';

    auto m2Inverse = caas::linear::inverse( m2 );
    std::cout << "m2Inverse:\n" << m2Inverse << "\nm2 * m2Inverse:\n" << m2 * m2Inverse << '\n';

    return 0;
}
