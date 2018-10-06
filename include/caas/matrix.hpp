#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>
#include <random>

#define N0OP ( ( void ) 0 )

#if !defined( NTRACE ) || !defined( NDEBUG )
#include <cstdio>
#define DETAILS std::printf( "[%s %s] %s:%d %s", __DATE__, __TIME__, __FILE__, __LINE__, __PRETTY_FUNCTION__ );
#else
#define DETAILS NOOP;
#endif

#ifndef NTRACE
#define TRACE DETAILS std::printf( "\n" );
#else
#define TRACE N0OP;
#endif

#ifndef NDEBUG
#define LOG_INFO( fmt, ... ) DETAILS std::printf( ": " fmt "\n", ##__VA_ARGS__ )
#else
#define LOG_INFO( fmt, ... ) NO0P
#endif

namespace caas
{
class Matrix
{
public:
    using value_type = double;

    Matrix() { TRACE }

    Matrix( std::size_t const rows, std::size_t const cols ) : rows_{ rows }, cols_{ cols }, size_{ rows_ * cols_ }
    { TRACE
        data_ = std::make_unique< value_type[] >( size_ );
    }

    Matrix( Matrix const & matrix ) : Matrix( matrix.rows_, matrix.cols_ )
    { TRACE
        std::copy( matrix.data_.get(), matrix.data_.get() + size_, data_.get() );
    }

    Matrix( Matrix && matrix ) :
        rows_{ matrix.rows_ },
        cols_{ matrix.cols_ },
        size_{ matrix.size_ },
        data_{ std::move( matrix.data_ ) }
    { TRACE
        matrix.rows_ = matrix.cols_ = matrix.size_ = 0;
    }

    ~Matrix() { TRACE }

    static inline Matrix Identity( std::size_t const rows, std::size_t const cols )
    { TRACE
        Matrix matrix{ rows, cols };
        matrix.setIdentity();
        return matrix;
    }

    static inline Matrix Identity( std::size_t const size )
    { TRACE
        return Identity( size, size );
    }

    static Matrix Random( std::size_t const rows, std::size_t const cols )
    { TRACE
        Matrix matrix{ rows, cols };
        matrix.setRandom();
        return matrix;
    }

    static inline Matrix Random( std::size_t const size )
    { TRACE
        return Random( size, size );
    }

    inline std::size_t rows() const { TRACE return rows_; }
    inline std::size_t cols() const { TRACE return cols_; }
    inline std::size_t size() const { TRACE return size_; }

    inline value_type operator()( std::size_t const row, std::size_t const col ) const
    { TRACE
        assert( row < rows_ );
        assert( col < cols_ );
        return data_[ cols_ * row + col ];
    }

    inline value_type & operator()( std::size_t const row, std::size_t const col )
    { TRACE
        assert( row < rows_ );
        assert( col < cols_ );
        return data_[ cols_ * row + col ];
    }

    inline Matrix & operator=( Matrix other )
    { TRACE
        std::swap( this->rows_, other.rows_ );
        std::swap( this->cols_, other.cols_ );
        std::swap( this->size_, other.size_ );
        std::swap( this->data_, other.data_ );
        return *this;
    }

    inline bool operator==( Matrix const & other ) noexcept
    { TRACE
        if ( rows_ != other.rows_ || cols_ != other.cols_ ) { return false; }
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            if ( data_[ i ] != other.data_[ i ] ) { return false; }
        }
        return true;
    }

    inline bool operator!=( Matrix const & other ) noexcept { TRACE return !( *this == other ); }

    inline Matrix & operator*=( Matrix const & other )
    {
        assert( cols_ == other.rows_ );
        Matrix result{ rows_, other.cols_ };
        for ( std::size_t i{ 0 }; i < result.rows_; ++i )
        {
            for ( std::size_t j{ 0 }; j < result.cols_; ++j )
            {
                value_type value{ 0 };
                for ( std::size_t k{ 0 }; k < cols_; ++k )
                {
                    value += ( *this )( i, k ) * other( k, j );
                }
                result( i, j ) = value;
            }
        }
        *this = std::move( result );
        return *this;
    }

    inline Matrix operator*( Matrix const & other ) const
    {
        assert( cols_ == other.rows_ );
        Matrix copy{ *this };
        copy *= other;
        return copy;
    }

    template< typename T >
    inline Matrix & operator*=( T const constant )
    { TRACE
        for ( auto & value : *this ) { value *= constant; }
        return *this;
    }

    template< typename T >
    inline Matrix operator*( T const constant ) const
    { TRACE
        Matrix copy{ *this };
        copy *= constant;
        return copy;
    }

    template< typename T >
    inline Matrix & operator/=( T const constant )
    { TRACE
        assert( constant != static_cast< T >( 0 ) );
        for ( auto & value : *this ) { value /= constant; }
        return *this;
    }

    template< typename T >
    inline Matrix operator/( T const constant ) const
    { TRACE
        Matrix copy{ *this };
        copy /= constant;
        return copy;
    }

    inline Matrix & operator+=( Matrix const & other )
    { TRACE
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            data_[ i ] += other.data_[ i ];
        }
        return *this;
    }

    inline Matrix operator+( Matrix const & other ) const
    { TRACE
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        Matrix copy{ other };
        copy += *this;
        return copy;
    }

    template< typename T >
    inline Matrix & operator+=( T const constant )
    { TRACE
        for ( auto & value : *this ) { value += constant; }
        return *this;
    }

    template< typename T >
    inline Matrix operator+( T const constant ) const
    { TRACE
        Matrix copy{ *this };
        copy += constant;
        return copy;
    }

    inline Matrix & operator-=( Matrix const & other )
    { TRACE
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            data_[ i ] -= other.data_[ i ];
        }
        return *this;
    }

    inline Matrix operator-( Matrix const & other ) const
    { TRACE
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        Matrix copy{ other };
        copy -= *this;
        return copy;
    }

    template< typename T >
    inline Matrix & operator-=( T const constant )
    { TRACE
        for ( auto & value : *this ) { value -= constant; };
        return *this;
    }

    template< typename T >
    inline Matrix operator-( T const constant ) const
    { TRACE
        Matrix copy{ *this };
        copy -= constant;
        return copy;
    }

    inline Matrix operator-() const
    { TRACE
        Matrix copy{ *this };
        for ( auto & value : copy ) { value = -value; }
        return copy;
    }

    inline Matrix operator~() const
    { TRACE
        return this->transpose();
    }

    friend inline std::ostream & operator<<( std::ostream & stream, Matrix const & matrix )
    { TRACE
        for ( std::size_t i{ 0 }; i < matrix.rows_; ++i )
        {
            for ( std::size_t j{ 0 }; j < matrix.cols_; ++j )
            {
                stream << matrix( i, j );
                if ( j + 1 < matrix.cols_ ) { stream << ' '; }
            }
            stream << '\n';
        }

        return stream;
    }

    inline Matrix transpose() const
    { TRACE
        Matrix copy{ this->cols_, this->rows_ };
        for ( std::size_t i{ 0 }; i < rows_; ++i )
        {
            for ( std::size_t j{ 0 }; j < cols_; ++j )
            {
                copy( j, i ) = ( *this )( i, j );
            }
        }
        return copy;
    }

    inline double * begin() noexcept { TRACE return data_.get();         }
    inline double * end()   noexcept { TRACE return data_.get() + size_; }

    inline Matrix & setRandom()
    { TRACE
        static std::random_device               randomDevice;
        static std::mt19937                     twisterEngine{ randomDevice() };
        static std::uniform_real_distribution<> distribution{ -1, 1 };

        for ( auto & value : *this ) { value = distribution( twisterEngine ); }

        return *this;
    }

    inline Matrix & setIdentity()
    { TRACE
        for ( std::size_t i{ 0 }; i < rows_; ++i )
        {
            for ( std::size_t j{ 0 }; j < cols_; ++j )
            {
                ( *this )( i, j ) = ( i == j ? 1 : 0 );
            }
        }
        return *this;
    }

    inline Matrix & setZero() noexcept { TRACE return setConstant( 0 ); }

    inline Matrix & setOnes() noexcept { TRACE return setConstant( 1 ); }

    inline Matrix & setConstant( value_type const constant ) noexcept
    { TRACE
        for ( auto & value : *this ) { value = constant; }
        return *this;
    }

    inline Matrix & fill( value_type const constant ) noexcept { TRACE return setConstant( constant ); }

private:
    std::size_t rows_;
    std::size_t cols_;
    std::size_t size_;
    std::unique_ptr< value_type[] > data_;
};

template< typename T >
Matrix operator*( T const constant, Matrix const & matrix )
{ TRACE
    return matrix * constant;
}

template< typename T >
Matrix operator/( T const constant, Matrix const & matrix )
{ TRACE
    return matrix / constant;
}

template< typename T >
Matrix operator+( T const constant, Matrix const & matrix )
{ TRACE
    return matrix + constant;
}

}

