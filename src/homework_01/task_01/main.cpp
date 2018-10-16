#include <caas/matrix.hpp>

#include <iostream>

int main()
{
    caas::Matrix a{ caas::Matrix::Random( 3, 4 ) };
    caas::Matrix b{ a };

    constexpr double pi{ 3.1415926535 };
    constexpr double precision{ 1e-5 };

    b = b * pi / pi;

    std::cout << "Matrix a:\n" << a << '\n';
    std::cout << "Matrix b:\n" << b << '\n';

    std::cout << "Matrix a == b: " << std::boolalpha << ( a == b ) << '\n';
    std::cout << "Matrix a ~= b (precision=" << precision << "): " << std::boolalpha << a.compare( b, precision ) << '\n';

    return 0;
}
