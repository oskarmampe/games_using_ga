#ifndef GENETICINDIVIDUAL_H
#define GENETICINDIVIDUAL_H
#include <string>
#include <map>
#include <QDebug>
#include <random>

// Random devices being seeded.
static std::random_device device;
static std::mt19937 engine(device());

/**
 *
 * Genetic Individual class representing a cell that can be genetically modified.
 * Throughout the class, and program, 0 represents cooperator and 1 defector.
 *
 * @brief The GeneticIndividual class
 */
class GeneticIndividual
{

public:
    // Encoding used by the individual. Defined in the report.
    enum ENCODING {CELLSTATE, ATTRIBUTE, AUTOMATA};

    // Initialise either as standard cooperator, or with a strategic strategy taken in as char.
    GeneticIndividual(ENCODING);
    GeneticIndividual(ENCODING, char);

    // Fitness function used to calcluate the new fitness value, which is then saved in a variable.
    double fitness_function(std::vector<char>, std::vector<std::vector<double>>);

    // Getters & Setters
    int get_gene_size();
    char get_strategy();
    double get_fitness();
    ENCODING get_encoding();
    void set_strategy(char);

    // Play and update the fitness value of the individual
    void play(std::vector<char>, std::vector<std::vector<double>>);

    // Individuals genetic genes
    bool* genes;


private:
    // Functions used to initialise the genetic individual
    void initialise(); // calls encode, and sets the default strategy, by either calling make_automata or setting the correct gene
    void encode(); // encodes the individual to a set of boolean values. Genes are intialised randomly.
    void make_automata(); // creates the automata so that it can be traversed/
    void traverse_automata(std::vector<char>); // traverses the automata, after playing with a neighbour.

    int get_random_int(int, int); // get a random number

    // Simple implementation of the automata using maps
    std::map<int, std::map<int,int>> automata;
    char automata_values[2];

    // Individual attributes.
    int state;
    ENCODING current;
    char strategy;
    int gene_size;
    double fitness;

};

#endif // GENETICINDIVIDUAL_H
