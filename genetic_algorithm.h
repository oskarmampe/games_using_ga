#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "geneticpopulation.h"
#include <QDebug>
#include <random>

class GeneticAlgorithm
{
    public:
        GeneticAlgorithm(int, std::vector<std::vector<double>>);
        std::vector<std::vector<GeneticIndividual>> simulate(std::vector<std::vector<GeneticIndividual>>);
    private:
        void selection();
        void mutation();
        GeneticIndividual crossover(std::vector<GeneticIndividual>);
        double play_with_neighbours(char, std::vector<char>);
        std::vector<std::vector<int>> get_neighbours(std::vector<int>);
        std::vector<std::vector<GeneticIndividual>> lattice;
        struct compare_class {
          bool operator() (GeneticIndividual i,GeneticIndividual j) { return (i.get_fitness()>j.get_fitness());}
        } compare;

        int generation;
        int dimension;
        std::vector<std::vector<double>> payoff_matrix;
};

#endif // GENETICALGORITHM_H
