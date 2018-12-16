#include <ecfcpp/ecfcpp.hpp>

#include <cstddef>
#include <iostream>

int main()
{
    constexpr auto decimalPrecision{ 5 };

    constexpr std::size_t numberOfComponents{ 3 };
    constexpr std::size_t populationSize{ 30 };

    constexpr bool        enableElitism{ true };
    constexpr std::size_t maxGenerations{ 1000000 };
    constexpr double      desiredFitness{ 0 };
    constexpr double      precision{ 1e-6 };

    constexpr std::size_t tournamentSize{ 3 };

    constexpr float mutationProbability{ 0.1 };
    constexpr bool  forceMutation{ true };

    constexpr auto logFrequency{ 10000 };

    using Chromosome = ecfcpp::BinaryArray< double, numberOfComponents >;

    constexpr auto function{ ecfcpp::function::CallCounter{ ecfcpp::function::shafferf7< Chromosome > } };

    auto const result
    {
        ecfcpp::ga::generational
        (
            enableElitism,
            maxGenerations,
            desiredFitness,
            precision,
            ecfcpp::problem::Minimization{ function },
            ecfcpp::selection::Tournament{ tournamentSize },
            ecfcpp::crossover::Uniform{},
            ecfcpp::mutation::BitFlip{ mutationProbability, forceMutation },
            ecfcpp::factory::create( Chromosome{ -50, 150, decimalPrecision }, populationSize, [](){ return ecfcpp::random::boolean(); } ),
            logFrequency
        )
    };

    std::cout << "Found solution in " << function.callCount() << " function evaluations.\n";
    std::cout << "  Fitness  = " << result.fitness << '\n';
    std::cout << "  Solution = " << result << '\n';

    return 0;
}

