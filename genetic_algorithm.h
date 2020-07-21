#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "geneticpopulation.h"
#include <QDebug>

class GeneticAlgorithm
{
    public:
        GeneticAlgorithm();
        void simulate();
    private:
        void selection();
        void mutation();
        void crossover();
        int generation;
        GeneticPopulation* pop;
        GeneticIndividual* least;
        GeneticIndividual* best;
};

#endif // GENETICALGORITHM_H
