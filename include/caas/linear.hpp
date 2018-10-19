#pragma once

#include "lup.hpp"
#include "supstitution.hpp"

#include <cassert>
#include <utility>

namespace caas::linear
{

void solve( Matrix & a, Matrix & b )
{
    assert( a.rows() == a.cols() );
    assert( a.rows() == b.rows() && b.cols() == 1 );

    decompose( a, b, Strategy::LUP );

    supstitution::forward( a, b );
    supstitution::backward( a, b );
}

Matrix solve( Matrix const & a, Matrix const & b )
{
    Matrix c{ a }, d{ b };
    solve( c, d );
    return d;
}


}
