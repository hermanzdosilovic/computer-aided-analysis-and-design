#include <caas/matrix.hpp>

#include <iostream>

int main()
{
    caas::Matrix a{ 2, 3 };
    a.setRandom();
    std::cout << a << '\n';
    std::cout << a*0.0 << '\n';
    std::cout << 100.0*a << '\n';
    std::cout << a << '\n';
    return 0;
}
