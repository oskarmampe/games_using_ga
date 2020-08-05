#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "geneticpopulation.h"
#include <QDebug>
#include <random>

class GeneticAlgorithm
{
    public:
        GeneticAlgorithm();
        std::vector<std::vector<GeneticIndividual>> simulate(int, std::vector<std::vector<double>>, std::vector<std::vector<GeneticIndividual>>, bool, int, int, bool);
    private:
        void selection(bool);
        void mutation(GeneticIndividual);
        GeneticIndividual crossover(std::vector<GeneticIndividual>);
        double play_with_neighbours(char, std::vector<char>);
        std::vector<std::vector<int>> get_neighbours(std::vector<int>);
        std::vector<std::vector<GeneticIndividual>> lattice;

        struct compare_class {
          bool operator() (GeneticIndividual i,GeneticIndividual j) { return (i.get_fitness()>j.get_fitness());}
        } compare;

        struct compare_tuple_class {
          bool operator() (std::tuple<std::vector<int>, GeneticIndividual> i, std::tuple<std::vector<int>, GeneticIndividual> j) { return (std::get<1>(i).get_fitness()>std::get<1>(j).get_fitness());}
        } compare_tuple;

        int generation;
        int dimension;
        std::vector<std::vector<double>> payoff_matrix;
        void neighbourhood_pop();
        void one_lattice_pop();
        int child_num;
        int parent_num;
        bool mut;
};

#endif // GENETICALGORITHM_H
