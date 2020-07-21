#include "geneticpopulation.h"

GeneticPopulation::GeneticPopulation()
{
    intitialise();
}

GeneticIndividual GeneticPopulation::get_fittest()
{
    std::sort(individuals.begin(), individuals.end(), compare);
}

void GeneticPopulation::intitialise()
{
    for (int i = 0; i < 5; ++i)
    {
        individuals.push_back(GeneticIndividual());
    }
}

