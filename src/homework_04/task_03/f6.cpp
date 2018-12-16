#include <ecfcpp/ecfcpp.hpp>

#include <cstddef>
#include <iostream>

int main()
{
    constexpr auto decimalPrecision{ 4 };

    constexpr std::size_t numberOfComponents{ 6 };
    constexpr std::size_t populationSize{ 10 };

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

    using BinaryChromosome  = ecfcpp::BinaryArray< double, numberOfComponents >;
    using DecimalChromosome = ecfcpp::Array< double, numberOfComponents >;

    constexpr auto binaryFunction{ ecfcpp::function::CallCounter{ ecfcpp::function::shafferf6< BinaryChromosome > } };
    constexpr auto decimalFunction{ ecfcpp::function::CallCounter{ ecfcpp::function::shafferf6< DecimalChromosome > } };

    std::cout << "f6 binary representation,f6 decimal representation\n";

    for ( auto i{ 0 }; i < 30; ++i )
    {
        std::cout <<
            ecfcpp::ga::generational
            (
                enableElitism,
                maxGenerations,
                desiredFitness,
                precision,
                ecfcpp::problem::Minimization{ binaryFunction },
                ecfcpp::selection::Tournament{ tournamentSize },
                ecfcpp::crossover::SinglePoint{},
                ecfcpp::mutation::BitFlip{ mutationProbability, forceMutation },
                ecfcpp::factory::create( BinaryChromosome{ -50, 150, decimalPrecision }, populationSize, [](){ return ecfcpp::random::boolean(); } ),
                logFrequency
            ).fitness;

        std::cout << ',';

        std::cout <<
            ecfcpp::ga::generational
            (
                enableElitism,
                maxGenerations,
                desiredFitness,
                precision,
                ecfcpp::problem::Minimization{ decimalFunction },
                ecfcpp::selection::Tournament{ tournamentSize },
                ecfcpp::crossover::BlxAlpha{ alpha },
                ecfcpp::mutation::Gaussian{ mutationProbability, forceMutation, sigma },
                ecfcpp::factory::create( DecimalChromosome{ -50, 150 }, populationSize, [](){ return ecfcpp::random::uniform( -50, 150 ); } ),
                logFrequency
            ).fitness;

        std::cout << '\n';
    }

    return 0;
}

