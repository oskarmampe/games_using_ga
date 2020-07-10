#include <tuple>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>

class Lattice 
{
    public:
        Lattice(int, std::vector<std::vector<double>>&);
        ~Lattice();
        void simulate(const int);
        std::vector<std::vector<char>> lattice;
        std::vector<std::vector<char>> old_lattice;
        void print_lattice();

    private:
        std::vector<std::vector<int>> get_neighbours(std::vector<int>);
        double play_with_neighbours(char, std::vector<char>);
        std::vector<std::vector<std::tuple<char, double>>> get_payoff_values();
        std::vector<std::vector<char>> update(std::vector<std::vector<std::tuple<char, double>>>);
        std::vector<std::vector<double>> payoff_matrix;
        int dimension;
};