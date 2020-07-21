#ifndef GENETICPOPULATION_H
#define GENETICPOPULATION_H
#include "geneticindividual.h"
#include <algorithm>    // std::sort
#include <vector>       // std::vector

class GeneticPopulation
{
public:
    GeneticPopulation();
    GeneticIndividual get_fittest();
    void intitialise();
    struct compare_class {
      bool operator() (GeneticIndividual i,GeneticIndividual j) { return (i.fitness_function()>j.fitness_function());}
    } compare;
    std::vector<GeneticIndividual> individuals;

private:
    //
};

#endif // GENETICPOPULATION_H
