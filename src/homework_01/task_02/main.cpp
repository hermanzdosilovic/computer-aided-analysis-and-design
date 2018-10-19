#include <caas/lup.hpp>

#include <iostream>

int main()
{
    caas::Matrix a{ "test_data/hw01/matrix1_t02.txt" };
    auto [ p1, lu1 ] = caas::decompose( a, caas::Strategy::LU ); // Silent failure is expected.
    std::cout << "p1:\n" << p1 << "\nlu1:\n" << lu1 << '\n';

    auto [ p2, lu2 ] = caas::decompose( a );
    std::cout << "p2:\n" << p2 << "\nlu2:\n" << lu2 << '\n';

    caas::Matrix b{ "test_data/hw01/vector1_t02.txt" };
    return 0;
}
