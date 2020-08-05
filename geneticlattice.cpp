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
    old_lattice = lattice;
    ga = new GeneticAlgorithm();
}

void GeneticLattice::set_e(double e)
{
    this->e = e;
    payoff_matrix.clear();
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};

    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);
}

void GeneticLattice::set_b(double b)
{
    this->b = b;
    payoff_matrix.clear();
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};

    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);
}

void GeneticLattice::set_dimension(int dimension)
{
    qDebug() << dimension;
    this->dimension = dimension;
    initialise_board(this->encoding);

}

void GeneticLattice::set_encoding(GeneticIndividual::ENCODING encoding)
{
    this->encoding = encoding;
    initialise_board(encoding);
    old_lattice = lattice;
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
    qDebug() << "lolz";
    int half = (int)((dimension-1)/2);
    lattice.at(half-1).at(half-1) = GeneticIndividual(encoding, 'd');
    lattice.at(half-1).at(half) = GeneticIndividual(encoding, 'd');
    lattice.at(half-1).at(half+1) = GeneticIndividual(encoding, 'd');
    lattice.at(half).at(half-1) = GeneticIndividual(encoding, 'd');
    lattice.at(half).at(half+1) = GeneticIndividual(encoding, 'd');
    lattice.at(half+1).at(half-1) = GeneticIndividual(encoding, 'd');
    lattice.at(half+1).at(half) = GeneticIndividual(encoding, 'd');
    lattice.at(half+1).at(half+1) = GeneticIndividual(encoding, 'd');
    lattice.at(half).at(half) = GeneticIndividual(encoding, 'd');
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

GeneticIndividual::ENCODING GeneticLattice::get_encoding()
{
    return encoding;
}


void GeneticLattice::simulate(std::string path, int parents, int children, bool global_pop, bool mut)
{
    old_lattice = lattice;
    lattice = ga->simulate(dimension, payoff_matrix, lattice, global_pop, parents, children, mut);
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
            std::string debug_s;
            for (int j = 0; j < dimension; ++j)
            {

               GeneticIndividual last_cell = old_lattice.at(i).at(j);

                if (last_cell.get_strategy() == 'c' && lattice.at(i).at(j).get_strategy() == 'c')
                {
                    img << "0" << " " << "0" << " " << "255" << std::endl;
                }
                else if (last_cell.get_strategy() == 'c' && lattice.at(i).at(j).get_strategy() == 'd')
                {
                    img << "255" << " " << "255" << " " << "0" << std::endl;
                }
                else if (last_cell.get_strategy() == 'd' && lattice.at(i).at(j).get_strategy() == 'd')
                {
                    img << "255" << " " << "0" << " " << "0" << std::endl;
                }
                else if (last_cell.get_strategy() == 'd' && lattice.at(i).at(j).get_strategy() == 'c')
                {
                    img << "0" << " " << "255" << " " << "0" << std::endl;
                }

//               debug_s = debug_s + lattice.at(i).at(j).get_strategy();
//               if (lattice.at(i).at(j).get_strategy() == 'c')
//               {
//                   img << "0" << " " << "0" << " " << "255" << std::endl;
//               }
//               else if (lattice.at(i).at(j).get_strategy() == 'd')
//               {
//                   img << "255" << " " << "0" << " " << "0" << std::endl;
//               }
            }
            //qDebug() << QString::fromStdString(debug_s);
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
    lattice.at(x).at(y).set_strategy(c);
}
