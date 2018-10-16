#include <caas/matrix.hpp>
#include <caas/lu.hpp>

#include <iostream>

int main()
{
    caas::Matrix m{ "A.txt" };
    std::cout << caas::decompose( m );
    return 0;
}
