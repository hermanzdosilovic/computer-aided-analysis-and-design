#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>

namespace caas
{

template< std::size_t N >
using Point = std::array< double, N >;

}

template< std::size_t N >
caas::Point< N > & operator+=( caas::Point< N > & p1, caas::Point< N > const & p2 )
{
    for ( auto i{ 0 }; i < N; ++i )
    {
        p1[ i ] += p2[ i ];
    }
    return p1;
}

template< std::size_t N >
caas::Point< N > operator+( caas::Point< N > const & p1, caas::Point< N > const & p2 )
{
    auto other{ p1 };
    other += p2;
    return other;
}

template< std::size_t N >
caas::Point< N > & operator-=( caas::Point< N > & p1, caas::Point< N > const & p2 )
{
    for ( std::size_t i{ 0 }; i < N; ++i )
    {
        p1[ i ] -= p2[ i ];
    }
    return p1;
}

template< std::size_t N >
caas::Point< N > operator-( caas::Point< N > const & p1, caas::Point< N > const & p2 )
{
    auto other{ p1 };
    other -= p2;
    return other;
}

template< std::size_t N >
bool operator<=( caas::Point< N > const & p1, caas::Point< N > const & p2 )
{
    for ( auto i{ 0 }; i < N; ++i )
    {
        if ( !( p1[ i ] <= p2[ i ] ) )
        {
            return false;
        }
    }
    return true;
}

template< std::size_t N >
double operator*( caas::Point< N > const & p1, caas::Point< N > const & p2 )
{
    double result{ 0 };
    for ( std::size_t i{ 0 }; i < N; ++i )
    {
        result += p1[ i ] * p2[ i ];
    }
    return result;
}

template< std::size_t N, typename T >
caas::Point< N > & operator*=( caas::Point< N > & p, T const t )
{
    for ( auto & i : p )
    {
        i *= t;
    }
    return p;
}

template< std::size_t N, typename T >
caas::Point< N > operator*( T const t, caas::Point< N > const & p )
{
    auto other{ p };
    other *= t;
    return other;
}

namespace std
{

template< std::size_t N >
caas::Point< N > abs( caas::Point< N > const & p )
{
    auto other{ p };
    for ( auto & i : other )
    {
        i = std::abs( i );
    }
    return other;
}

template< std::size_t N >
double norm( caas::Point< N > const & p )
{
    return std::sqrt( p * p );
}

template< std::size_t N >
std::ostream & operator<<( std::ostream & stream, caas::Point< N > const & p )
{
    stream << "{";
    for( std::size_t i{ 0 }; i < N; ++i )
    {
        stream << p[ i ];
        if ( i + 1 < N )
        {
            stream << ", ";
        }
    }
    stream << "}";

    return stream;
}


template< std::size_t N >
std::string to_string( caas::Point< N > const & p )
{
    std::ostringstream stream;
    stream << p;
    return stream.str();
}

}
