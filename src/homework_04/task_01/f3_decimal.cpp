#include <ecfcpp/ecfcpp.hpp>

#include <iostream>

int main()
{
    using Chromosome = ecfcpp::Array< float, 5 >;

    Chromosome x;
    std::cout << x << '\n';

    return 0;
}
