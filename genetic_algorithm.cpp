#include "genetic_algorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
    pop = new GeneticPopulation();
    generation = 0;
}

void GeneticAlgorithm::simulate()
{
    while (generation < 5)
    {
        qDebug() << "Fittest";
        pop->get_fittest();
        qDebug() << "SELECTION";
        selection();
        qDebug() << "CROSSOVER";
        crossover();
        qDebug() << "MUTATION";
        mutation();
        qDebug() << "CHANGE";
        *least = *best;
        generation++;
    }
    pop->get_fittest();
    for (int i = 0; i < pop->individuals.size(); ++i)
    {
        qDebug() << "-----------------------------------------";
        qDebug() << "Individual at location i: " + QString(i) + " with genes: ";
        for (int j = 0; j < 5; ++j)
        {
            qDebug() << " " + QString(pop->individuals.at(i).genes[j]) + " ";
        }
        qDebug() << "and fitness: " + QString::number(pop->individuals.at(i).fitness_function());
        qDebug() << "-----------------------------------------";
    }
}

void GeneticAlgorithm::selection()
{
    least = &pop->individuals.at(0);
    best = &pop->individuals.at(pop->individuals.size()-1);
}

void GeneticAlgorithm::mutation()
{
    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 1 and 10: */
    int mutation_point = rand() % 5 + 1;
    pop->individuals.at(0).genes[mutation_point] = pop->individuals.at(0).genes[mutation_point] == 0 ? 1 : 0;
    srand (time(NULL));
    int mutation_point_2 = rand() % 5 + 1;
    pop->individuals.at(1).genes[mutation_point_2] = pop->individuals.at(1).genes[mutation_point_2] == 0 ? 1 : 0;
}

void GeneticAlgorithm::crossover()
{
    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 1 and 10: */
    int crossover_point = rand() % 5 + 1;

    for (int i = 0; i < crossover_point; ++i)
    {
        bool temp = pop->individuals.at(0).genes[i];
        pop->individuals.at(0).genes[i] = pop->individuals.at(1).genes[i];
        pop->individuals.at(1).genes[i] = temp;
    }
}
