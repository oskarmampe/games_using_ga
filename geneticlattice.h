#ifndef LATTICE_H
#define LATTICE_H
#include <tuple>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include "geneticindividual.h"
#include "genetic_algorithm.h"
class GeneticLattice
{
public:
    GeneticLattice(int, double, double);

    double get_b();
    double get_e();
    int get_dimension();

    void set_b(double);
    void set_e(double);
    void set_dimension(int);

    void initialise_board(GeneticIndividual::ENCODING);

    void simulate(std::string);

    void save_lattice(std::string);
    void change_lattice(int, int, char);

private:
    int dimension;
    double e;
    double b;
    GeneticIndividual::ENCODING encoding;
    GeneticAlgorithm* ga;

    std::vector<std::vector<GeneticIndividual>> lattice;
    std::vector<std::vector<GeneticIndividual>> old_lattice;
    std::vector<std::vector<double>> payoff_matrix;


};

#endif // LATTICE_H
