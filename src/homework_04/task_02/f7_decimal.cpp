#include <ecfcpp/ecfcpp.hpp>

#include <cstddef>
#include <iostream>

int main()
{
    constexpr std::size_t numberOfComponents{ 2 };
    constexpr std::size_t populationSize{ 10 };

    constexpr bool        enableElitism{ true };
    constexpr std::size_t maxGenerations{ 1000000 };
    constexpr double      desiredFitness{ 0 };
    constexpr double      precision{ 1e-6 };

    constexpr std::size_t tournamentSize{ 3 };

    constexpr float alpha{ 0.1 };

    constexpr float mutationProbability{ 0.0 };
    constexpr bool  forceMutation{ true };
    constexpr float sigma{ 0.1 };

    constexpr auto logFrequency{ 10000 };

    using Chromosome = ecfcpp::Array< double, numberOfComponents >;

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
            ecfcpp::crossover::BlxAlpha{ alpha },
            ecfcpp::mutation::Gaussian{ mutationProbability, forceMutation, sigma },
            ecfcpp::factory::create( Chromosome{ -50, 150 }, populationSize, [](){ return ecfcpp::random::uniform( -50, 150 ); } ),
            logFrequency
        )
    };

    std::cout << "Found solution in " << function.callCount() << " function evaluations.\n";
    std::cout << "  Fitness  = " << result.fitness << '\n';
    std::cout << "  Solution = " << result << '\n';

    return 0;
}

