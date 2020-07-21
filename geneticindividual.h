#ifndef GENETICINDIVIDUAL_H
#define GENETICINDIVIDUAL_H
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class GeneticIndividual
{
public:
    GeneticIndividual();
    double fitness_function();
    bool genes[5];

private:
    //
};

#endif // GENETICINDIVIDUAL_H
