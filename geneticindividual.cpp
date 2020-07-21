#include "geneticindividual.h"

GeneticIndividual::GeneticIndividual()
{
    int len = sizeof(genes)/sizeof(genes[0]);
    for (int i = 0; i < len; ++i)
    {
        /* initialize random seed: */
        srand(time(NULL));
        genes[i] = rand() % 10 + 1 < 5 ? false : true;
    }
}

double GeneticIndividual::fitness_function()
{
    double fitness = 0;
    int len = sizeof(genes)/sizeof(genes[0]);
    for (int i = 0; i < len; ++i)
    {
        if (genes[i] == 1) {
            fitness += i;
        }
    }
    return fitness;
}
