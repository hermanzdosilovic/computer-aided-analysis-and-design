#include <ecfcpp/ecfcpp.hpp>

#include <cstddef>
#include <iostream>

int main()
{
    constexpr std::size_t numberOfComponents{ 6 };
    constexpr std::size_t populationSizes[]{ 3, 50, 100, 200 };

    constexpr bool        enableElitism{ true };
    constexpr std::size_t maxGenerations{ 100000 };
    constexpr double      desiredFitness{ 0 };
    constexpr double      precision{ 1e-6 };

    constexpr std::size_t tournamentSize{ 3 };

    constexpr float alpha{ 0.1 };

    constexpr float mutationProbability{ 0.1 };
    constexpr bool  forceMutation{ true };
    constexpr float sigma{ 0.1 };

    constexpr auto logFrequency{ 0 };

    using Chromosome = ecfcpp::Array< double, numberOfComponents >;

    constexpr auto function{ ecfcpp::function::CallCounter{ ecfcpp::function::shafferf6< Chromosome > } };

    std::cout << "f6 30,f6 50,f6 100,f6 200\n";

    for ( auto i{ 0 }; i < 30; ++i )
    {
        char separator[]{ '\0',  '\0' };
        for ( auto populationSize : populationSizes )
        {
            std::cout << separator;
            std::cout <<
                ecfcpp::ga::generational
                (
                    enableElitism,
                    maxGenerations,
                    desiredFitness,
                    precision,
                    ecfcpp::problem::Minimization{ function },
                    ecfcpp::selection::Tournament{ tournamentSize },
                    ecfcpp::crossover::BlxAlpha{ alpha },
                    ecfcpp::mutation::Gaussian{ mutationProbability, forceMutation, sigma },
                    ecfcpp::factory::create( Chromosome{ -50, 150 }, populationSize, [](){ return ecfcpp::random::uniform( -50, 150 ); } ),
                    logFrequency
                ).fitness;
            separator[ 0 ] = ',';
        }
        std::cout << '\n';
    }

    return 0;
}

