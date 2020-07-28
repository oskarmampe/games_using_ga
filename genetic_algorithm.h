#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "geneticpopulation.h"
#include <QDebug>

class GeneticAlgorithm
{
    public:
        GeneticAlgorithm(int, std::vector<std::vector<double>>);
        std::vector<std::vector<GeneticIndividual>> simulate(std::vector<std::vector<GeneticIndividual>>);
    private:
        void selection();
        void mutation();
        void crossover();
        double play_with_neighbours(char, std::vector<char>);
        std::vector<std::vector<int>> get_neighbours(std::vector<int>);
        std::vector<std::vector<GeneticIndividual>> lattice;

        int generation;
        int dimension;
        std::vector<std::vector<double>> payoff_matrix;
};

#endif // GENETICALGORITHM_H
