#ifndef LATTICE_H
#define LATTICE_H

#include <tuple>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <regex>
#include "geneticindividual.h"
#include "genetic_algorithm.h"

/**
 *
 * A genetic lattice class. This class has the Genetic Algorithm class, and passes the lattice to genetic algorithm.
 *
 * @brief The GeneticLattice class
 */
class GeneticLattice
{
public:
    GeneticLattice(int, double, double);

    // Getters & Setters
    double get_b();
    double get_e();
    int get_dimension();
    GeneticIndividual::ENCODING get_encoding();
    GeneticIndividual get_cell(int, int);

    void set_b(double);
    void set_e(double);
    void set_dimension(int);
    void set_encoding(GeneticIndividual::ENCODING);

    // Initialise the baord with genetic individuals
    void initialise_board();

    // Simulate a genetic evolutionary game.
    void simulate(std::string, int, int, bool, bool);

    // Save the lattice
    void save_lattice(std::string);

    // Change an individuals strategy
    void change_lattice(int, int, char);

private:

    // Genetic lattice attributes
    int dimension;
    double e;
    double b;
    bool first_save; // boolean to check whether it is a first save, to add csv headers
    GeneticIndividual::ENCODING encoding;
    GeneticAlgorithm* ga;

    std::vector<std::vector<GeneticIndividual>> lattice;
    std::vector<std::vector<GeneticIndividual>> old_lattice; // needed to see the changes from previous generation
    std::vector<std::vector<double>> payoff_matrix;


};

#endif // LATTICE_H
