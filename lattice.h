#ifndef LATTICE_H
#define LATTICE_H
#include <tuple>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>

class Lattice
{
public:
    Lattice(int, double, double);

    double get_b();
    double get_e();
    int get_dimension();

    void set_b(double);
    void set_e(double);
    void set_dimension(int);

    void initialise_board();

    void simulate(std::string);

    void save_lattice(std::string);
    void change_lattice(int, int, char);

private:
    int dimension;
    double e;
    double b;

    std::vector<std::vector<char>> lattice;
    std::vector<std::vector<char>> old_lattice;
    std::vector<std::vector<double>> payoff_matrix;

    std::vector<std::vector<int>> get_neighbours(std::vector<int>);
    double play_with_neighbours(char, std::vector<char>);
    std::vector<std::vector<std::tuple<char, double>>> get_payoff_values();
    std::vector<std::vector<char>> update(std::vector<std::vector<std::tuple<char, double>>>);


};

#endif // LATTICE_H
