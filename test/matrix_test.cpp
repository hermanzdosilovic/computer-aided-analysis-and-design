#include <caas/matrix.hpp>

#include <catch2/catch.hpp>

#include <utility>

SCENARIO( "matrix can have arbitrary size", "[matrix]" )
{
    GIVEN( "arbitrary size matrix" )
    {
        constexpr std::size_t rows{ 5 };
        constexpr std::size_t cols{ 3 };

        caas::Matrix const m{ rows, cols };

        WHEN( "the size is checked" )
        {
            auto const & matrixRows{ m.rows() };
            auto const & matrixCols{ m.cols() };

            THEN( "the size is the same as when matrix was defined" )
            {
                REQUIRE( matrixRows == rows );
                REQUIRE( matrixCols == cols );
            }
        }
    }
}

SCENARIO( "inserting elements to matrix", "[matrix]" )
{
    GIVEN( "matrix of doubles" )
    {
        caas::Matrix m{ 3, 2 };

        WHEN( "element is inserted at position (0, 0)" )
        {
            constexpr double value{ 10.0f };
            m( 0, 0 ) = value;

            THEN( "element can be accessed" )
            {
                REQUIRE( m( 0, 0 ) == value );
            }
        }

        WHEN( "element is inserted at position (0, 1)" )
        {
            constexpr double value{ 5.0f };
            m( 0, 1 ) = value;

            THEN( "element can be accessed" )
            {
                REQUIRE( m( 0, 1 ) == value );
            }
        }

        WHEN( "element is inserted at every position" )
        {
            for ( std::size_t i{ 0 }; i < m.rows(); ++i )
            {
                for ( std::size_t j{ 0 }; j < m.cols(); ++j )
                {
                    m( i, j ) = i + j;
                }
            }

            THEN( "every can be accessed" )
            {

                for ( std::size_t i{ 0 }; i < m.rows(); ++i )
                {
                    for ( std::size_t j{ 0 }; j < m.cols(); ++j )
                    {
                        REQUIRE( m( i, j ) == i + j );
                    }
                }
            }
        }
    }
}

SCENARIO( "copy constructor", "[matrix]" )
{
    GIVEN( "matrix of arbitrary size and with arbitrary elements" )
    {
        caas::Matrix a{ 3, 4 };
        for ( std::size_t i{ 0 }; i < a.rows(); ++i )
        {
            for ( std::size_t j{ 0 }; j < a.cols(); ++j )
            {
                a( i, j ) = 2 * i + j;
            }
        }

        WHEN( "copy constructor is used" )
        {
            caas::Matrix b{ a };
            THEN ( "number of rows and cols should be preserved" )
            {
                REQUIRE( a.rows() == b.rows() );
                REQUIRE( a.cols() == b.cols() );
            }

            AND_THEN( "all elements should be the same" )
            {
                for ( std::size_t i{ 0 }; i < a.rows(); ++i )
                {
                    for ( std::size_t j{ 0 }; j < a.cols(); ++j )
                    {
                        REQUIRE( a( i, j ) == b( i, j ) );
                    }
                }
            }
        }
    }
}

SCENARIO( "move constructor", "[matrix]" )
{
    GIVEN( "matrix of arbitrary size and with arbitrary elements" )
    {
        caas::Matrix a{ 3, 4 };
        for ( std::size_t i{ 0 }; i < a.rows(); ++i )
        {
            for ( std::size_t j{ 0 }; j < a.cols(); ++j )
            {
                a( i, j ) = 2 * i + j;
            }
        }

        WHEN( "move constructor is used" )
        {
            caas::Matrix c{ a }; /* This copy assumes that copy constructor works. */
            caas::Matrix b{ std::move( a ) };
            THEN ( "number of rows and cols should be preserved" )
            {
                REQUIRE( c.rows() == b.rows() );
                REQUIRE( c.cols() == b.cols() );
            }

            AND_THEN( "all elements should be the same" )
            {
                for ( std::size_t i{ 0 }; i < c.rows(); ++i )
                {
                    for ( std::size_t j{ 0 }; j < c.cols(); ++j )
                    {
                        REQUIRE( c( i, j ) == b( i, j ) );
                    }
                }
            }
        }
    }
}
