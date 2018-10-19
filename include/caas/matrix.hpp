#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <istream>
#include <iterator>
#include <memory>
#include <ostream>
#include <random>
#include <sstream>
#include <string_view>
#include <utility>

namespace caas
{
class Matrix
{
public:
    using value_type = double;

    Matrix() = default;

    Matrix( std::size_t const rows, std::size_t const cols ) : rows_{ rows }, cols_{ cols }, size_{ rows_ * cols_ }
    {
        data_ = std::make_unique< value_type[] >( size_ );
    }

    Matrix( Matrix const & matrix ) : Matrix( matrix.rows_, matrix.cols_ )
    {
        std::copy( matrix.data_.get(), matrix.data_.get() + size_, data_.get() );
    }

    Matrix( Matrix && matrix ) :
        rows_{ matrix.rows_ },
        cols_{ matrix.cols_ },
        size_{ matrix.size_ },
        data_{ std::move( matrix.data_ ) }
    {
        matrix.rows_ = matrix.cols_ = matrix.size_ = 0;
    }

    Matrix( std::string_view const & filePath )
    {
        std::ifstream file{ filePath.data(), std::ios_base::in };
        Matrix tmp;
        file >> tmp;
        file.close();
        *this = std::move( tmp );
    }

    ~Matrix() = default;

    static Matrix Identity( std::size_t const rows, std::size_t const cols )
    {
        Matrix matrix{ rows, cols };
        matrix.setIdentity();
        return matrix;
    }

    static Matrix Identity( std::size_t const size )
    {
        return Identity( size, size );
    }

    static Matrix Random( std::size_t const rows, std::size_t const cols )
    {
        Matrix matrix{ rows, cols };
        matrix.setRandom();
        return matrix;
    }

    static Matrix Random( std::size_t const size )
    {
        return Random( size, size );
    }

    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }
    std::size_t size() const { return size_; }

    value_type operator()( std::size_t const row, std::size_t const col ) const
    {
        assert( row < rows_ );
        assert( col < cols_ );
        return data_[ cols_ * row + col ];
    }

    value_type & operator()( std::size_t const row, std::size_t const col )
    {
        assert( row < rows_ );
        assert( col < cols_ );
        return data_[ cols_ * row + col ];
    }

    Matrix & operator=( Matrix other )
    {
        std::swap( this->rows_, other.rows_ );
        std::swap( this->cols_, other.cols_ );
        std::swap( this->size_, other.size_ );
        std::swap( this->data_, other.data_ );
        return *this;
    }

    bool operator==( Matrix const & other ) noexcept
    {
        if ( rows_ != other.rows_ || cols_ != other.cols_ ) { return false; }
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            if ( data_[ i ] != other.data_[ i ] ) { return false; }
        }
        return true;
    }

    bool compare( Matrix const & other, double const precision = 1e-15 ) noexcept
    {
        if ( rows_ != other.rows_ || cols_ != other.cols_ ) { return false; }
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            if ( std::abs( data_[ i ] - other.data_[ i ] ) > precision ) { return false; }
        }
        return true;
    }

    bool operator!=( Matrix const & other ) noexcept { return !( *this == other ); }

    Matrix & operator*=( Matrix const & other )
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

    Matrix operator*( Matrix const & other ) const
    {
        assert( cols_ == other.rows_ );
        Matrix copy{ *this };
        copy *= other;
        return copy;
    }

    template< typename T >
    Matrix & operator*=( T const constant )
    {
        for ( auto & value : *this ) { value *= constant; }
        return *this;
    }

    template< typename T >
    Matrix operator*( T const constant ) const
    {
        Matrix copy{ *this };
        copy *= constant;
        return copy;
    }

    template< typename T >
    Matrix & operator/=( T const constant )
    {
        assert( constant != static_cast< T >( 0 ) );
        for ( auto & value : *this ) { value /= constant; }
        return *this;
    }

    template< typename T >
    Matrix operator/( T const constant ) const
    {
        Matrix copy{ *this };
        copy /= constant;
        return copy;
    }

    Matrix & operator+=( Matrix const & other )
    {
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            data_[ i ] += other.data_[ i ];
        }
        return *this;
    }

    Matrix operator+( Matrix const & other ) const
    {
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        Matrix copy{ other };
        copy += *this;
        return copy;
    }

    template< typename T >
    Matrix & operator+=( T const constant )
    {
        for ( auto & value : *this ) { value += constant; }
        return *this;
    }

    template< typename T >
    Matrix operator+( T const constant ) const
    {
        Matrix copy{ *this };
        copy += constant;
        return copy;
    }

    Matrix & operator-=( Matrix const & other )
    {
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        for ( std::size_t i{ 0 }; i < size_; ++i )
        {
            data_[ i ] -= other.data_[ i ];
        }
        return *this;
    }

    Matrix operator-( Matrix const & other ) const
    {
        assert( rows_ == other.rows_ );
        assert( cols_ == other.cols_ );
        Matrix copy{ other };
        copy -= *this;
        return copy;
    }

    template< typename T >
    Matrix & operator-=( T const constant )
    {
        for ( auto & value : *this ) { value -= constant; };
        return *this;
    }

    template< typename T >
    Matrix operator-( T const constant ) const
    {
        Matrix copy{ *this };
        copy -= constant;
        return copy;
    }

    Matrix operator-() const
    {
        Matrix copy{ *this };
        for ( auto & value : copy ) { value = -value; }
        return copy;
    }

    Matrix operator~() const
    {
        return this->transpose();
    }

    friend std::ostream & operator<<( std::ostream & stream, Matrix const & matrix )
    {
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

    friend std::istream & operator>>( std::istream & stream, caas::Matrix & matrix )
    {
        std::size_t rows{ 0 };
        std::vector< value_type > values;
        for ( std::string line; std::getline( stream, line ); )
        {
            std::istringstream stringStream( line );
            bool picked_first{ false };
            for ( value_type tmp; stringStream >> tmp; )
            {
                if ( !picked_first )
                {
                    picked_first = true;
                    ++rows;
                }
                values.push_back( tmp );
            }
        }

        assert( std::size( values ) % rows == 0 );

        matrix = Matrix{ rows, std::size( values ) / rows };
        for ( std::size_t i{ 0 }; i < std::size( values ); ++i )
        {
            matrix.data_[ i ] = values[ i ];
        }

        return stream;
    }

    Matrix transpose() const
    {
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

    void swapRows( std::size_t const i, std::size_t const j ) noexcept
    {
        assert( i < rows_ );
        assert( j < rows_ );
        for ( std::size_t k{ 0 }; k < cols_; ++k )
        {
            std::swap( ( *this )( i, k ), ( *this )( j, k ) );
        }
    }

    void swapCols( std::size_t const i, std::size_t const j ) noexcept
    {
        assert( i < cols_ );
        assert( j < cols_ );
        for ( std::size_t k{ 0 }; k < rows_; ++k )
        {
            std::swap( ( *this )( k, i ), ( *this )( k, j ) );
        }
    }

    double * const begin() noexcept { return data_.get();         }
    double * const end()   noexcept { return data_.get() + size_; }

    double const * const begin() const noexcept { return data_.get();         }
    double const * const end()   const noexcept { return data_.get() + size_; }

    Matrix & setRandom()
    {
        static std::random_device               randomDevice;
        static std::mt19937                     twisterEngine{ randomDevice() };
        static std::uniform_real_distribution<> distribution{ -1, 1 };

        for ( auto & value : *this ) { value = distribution( twisterEngine ); }

        return *this;
    }

    Matrix & setIdentity()
    {
        for ( std::size_t i{ 0 }; i < rows_; ++i )
        {
            for ( std::size_t j{ 0 }; j < cols_; ++j )
            {
                ( *this )( i, j ) = ( i == j ? 1 : 0 );
            }
        }
        return *this;
    }

    Matrix & setZero() noexcept { return setConstant( 0 ); }

    Matrix & setOnes() noexcept { return setConstant( 1 ); }

    Matrix & setConstant( value_type const constant ) noexcept
    {
        for ( auto & value : *this ) { value = constant; }
        return *this;
    }

    Matrix & fill( value_type const constant ) noexcept { return setConstant( constant ); }

private:
    std::size_t rows_{};
    std::size_t cols_{};
    std::size_t size_{};
    std::unique_ptr< value_type[] > data_;
};

template< typename T >
Matrix operator*( T const constant, Matrix const & matrix )
{
    return matrix * constant;
}

template< typename T >
Matrix operator/( T const constant, Matrix const & matrix )
{
    return matrix / constant;
}

template< typename T >
Matrix operator+( T const constant, Matrix const & matrix )
{
    return matrix + constant;
}

}

