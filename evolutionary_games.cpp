#include "lattice.h"
#include <iostream>

int main()
{
    Lattice lattice(100, std::vector<std::vector<double>>{std::vector<double>{1,0}, std::vector<double>{1.65, 0}});

    lattice.simulate(64);

    lattice.print_lattice();
}