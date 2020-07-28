#include "geneticlattice.h"
#include <QDebug>

GeneticLattice::GeneticLattice(int dimension, double b, double e)
{
    this->dimension = dimension;
    this->e = e;
    this->b = b;
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};

    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);

    initialise_board(GeneticIndividual::AUTOMATA);
    ga = new GeneticAlgorithm(dimension, payoff_matrix);
}

void GeneticLattice::set_e(double e)
{
    this->e = e;
}

void GeneticLattice::set_b(double b)
{
    this->b = b;
}

void GeneticLattice::set_dimension(int dimension)
{
    qDebug() << dimension;
    this->dimension = dimension;
    initialise_board(this->encoding);

}

void GeneticLattice::initialise_board(GeneticIndividual::ENCODING encoding)
{
    lattice.clear();
    this->encoding = encoding;
    for (int i = 0; i < dimension; ++i)
    {
        std::vector<GeneticIndividual> temp;

        for (int j = 0; j < dimension; ++j)
        {
            temp.push_back(GeneticIndividual(encoding));
        }
        lattice.push_back(temp);
    }

    lattice[(int)((dimension-1)/2)][(int)((dimension-1)/2)] = GeneticIndividual(encoding, 'd');
}

double GeneticLattice::get_e()
{
    return e;
}

double GeneticLattice::get_b()
{
    return b;
}

int GeneticLattice::get_dimension()
{
    return dimension;
}


void GeneticLattice::simulate(std::string path)
{
    old_lattice = lattice;
    lattice = ga->simulate(lattice);
    save_lattice(path);
}

void GeneticLattice::save_lattice(std::string path)
{
    std::ofstream img;
    img.open(path);


    if (img.is_open())
    { // proceed with output
        img << "P3" << std::endl;
        img << dimension << " " << dimension << std::endl;
        img << "255" << std::endl;

        for (int i = 0; i < dimension; ++i)
        {
            for (int j = 0; j < dimension; ++j)
            {

                if (lattice[i][j].get_strategy() == 'c')
                {
                    img << "0" << " " << "255" << " " << "0" << std::endl;
                }
                else if (lattice[i][j].get_strategy() == 'd')
                {
                    img << "255" << " " << "0" << " " << "0" << std::endl;
                }
            }
        }
        img.close();
    }
    else
    {
        throw std::runtime_error("Could not open file");
    }
}

void GeneticLattice::change_lattice(int x, int y, char c)
{
    lattice[x][y].set_strategy(c);
}
