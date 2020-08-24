#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "geneticindividual.h"
#include <QDebug>
#include <random>
#include <vector>
#include <algorithm>

/**
 *
 * Genetic Algorithm class which implements the genetic algorithm for a genetic lattice.
 * Genetic Algorithm parameters are passed to the simulate function itself.
 *
 * @brief The GeneticAlgorithm class
 */
class GeneticAlgorithm
{
    public:
        GeneticAlgorithm();

        std::vector<std::vector<GeneticIndividual>> simulate(int, // dimension
                                                             std::vector<std::vector<double>>, // payoff matrix
                                                             std::vector<std::vector<GeneticIndividual>>, // lattice
                                                             bool, // global
                                                             int, // parents
                                                             int, // children
                                                             bool); // mutation
    private:
        // Genetic Algorithm operators
        void selection(bool);
        void mutation(GeneticIndividual);
        GeneticIndividual crossover(std::vector<GeneticIndividual>);

        // Different ways of selecting from populations.
        void neighbourhood_pop();
        void one_lattice_pop();

        // Both of these functions are based off of the simple python version; needed for any spatial game.
        double play_with_neighbours(char, std::vector<char>); // was updated to take from genetic individuals instead.
        std::vector<std::vector<int>> get_neighbours(std::vector<int>); // same as python with syntax changes

        // Compare classes used for sorting an array of genetic individuals. Needed for <std/algorithm>
        struct compare_class {
          bool operator() (GeneticIndividual i,GeneticIndividual j) { return (i.get_fitness()>j.get_fitness());}
        } compare;

        struct compare_tuple_class {
          bool operator() (std::tuple<std::vector<int>, GeneticIndividual> i, std::tuple<std::vector<int>, GeneticIndividual> j) { return (std::get<1>(i).get_fitness()>std::get<1>(j).get_fitness());}
        } compare_tuple;


        // Genetic algorithm parameters
        std::vector<std::vector<GeneticIndividual>> lattice;
        int generation;
        int dimension;
        std::vector<std::vector<double>> payoff_matrix;
        int child_num;
        int parent_num;
        bool mut;

        // Random number functions.
        int get_random_distribution(std::vector<double>::iterator, std::vector<double>::iterator);
        int get_random_int(int, int);
};

#endif // GENETICALGORITHM_H
