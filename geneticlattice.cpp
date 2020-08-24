#include "geneticlattice.h"
#include <QDebug>

/**
 *
 * Initialise a genetic lattice, with a dimension, b and e.
 *
 * @brief GeneticLattice::GeneticLattice
 * @param dimension
 * @param b: second row first column value
 * @param e: second row second column value
 */
GeneticLattice::GeneticLattice(int dimension, double b, double e)
{
    // Initialise default attributes
    this->dimension = dimension;
    this->e = e;
    this->b = b;
    this->first_save = true;
    this->encoding = GeneticIndividual::AUTOMATA;

    // Create a payoff matrix
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};

    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);

    // Initialise the board
    initialise_board();
    old_lattice = lattice;

    // Create a genetic algorithm
    ga = new GeneticAlgorithm();

}

/**
 *
 * e setter
 *
 * @brief GeneticLattice::set_e
 * @param e
 */
void GeneticLattice::set_e(double e)
{
    this->e = e;
    payoff_matrix.clear();
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};

    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);
}

/**
 *
 * b setter
 *
 * @brief GeneticLattice::set_b
 * @param b
 */
void GeneticLattice::set_b(double b)
{
    this->b = b;
    payoff_matrix.clear();
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};

    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);
}

/**
 *
 * Dimension setter
 *
 * @brief GeneticLattice::set_dimension
 * @param dimension
 */
void GeneticLattice::set_dimension(int dimension)
{
    if(dimension > 0)
    {
        this->dimension = dimension;
        initialise_board();
    }
    else
    {
        qDebug() << "Invalid dimension";
    }
}

/**
 *
 * Encoding setter
 *
 * @brief GeneticLattice::set_encoding
 * @param encoding
 */
void GeneticLattice::set_encoding(GeneticIndividual::ENCODING encoding)
{
    this->encoding = encoding;
    initialise_board();
    old_lattice = lattice;
}

/**
 *
 * Initialise the board with individuals
 *
 * @brief GeneticLattice::initialise_board
 */
void GeneticLattice::initialise_board()
{
    lattice.clear(); // reset the lattice
    for (int i = 0; i < dimension; ++i)
    {
        std::vector<GeneticIndividual> temp;

        for (int j = 0; j < dimension; ++j)
        {
            temp.push_back(GeneticIndividual(encoding));
        }
        lattice.push_back(temp);
    }

    // Create a defector 3 by 3 square by default
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

/**
 *
 * e getter
 *
 * @brief GeneticLattice::get_e
 * @return
 */
double GeneticLattice::get_e()
{
    return e;
}

/**
 *
 * b getter
 *
 * @brief GeneticLattice::get_b
 * @return
 */
double GeneticLattice::get_b()
{
    return b;
}

/**
 *
 * Dimension getter
 *
 * @brief GeneticLattice::get_dimension
 * @return
 */
int GeneticLattice::get_dimension()
{
    return dimension;
}

/**
 *
 * Encoding getter
 *
 * @brief GeneticLattice::get_encoding
 * @return
 */
GeneticIndividual::ENCODING GeneticLattice::get_encoding()
{
    return encoding;
}

/**
 *
 * Cell getter
 *
 * @brief GeneticLattice::get_cell
 * @param i: row
 * @param j: column
 * @return genetic individual at i,j
 */
GeneticIndividual GeneticLattice::get_cell(int i, int j)
{
    return lattice.at(i).at(j);
}


/**
 *
 * Simulate using a genetic algorithm
 *
 * @brief GeneticLattice::simulate
 * @param path: path to save
 * @param parents
 * @param children
 * @param global_pop : global or local/neighbourhood
 * @param mut: mutation or not
 */
void GeneticLattice::simulate(std::string path, int parents, int children, bool global_pop, bool mut)
{
    old_lattice = lattice;
    lattice = ga->simulate(dimension, payoff_matrix, lattice, global_pop, parents, children, mut);
    save_lattice(path);
}

/**
 *
 * Save the lattice
 *
 * @brief GeneticLattice::save_lattice
 * @param path
 */
void GeneticLattice::save_lattice(std::string path)
{
    // Open the image file
    std::ofstream img;
    img.open(path);

    // Open the csv file
    std::ofstream csv;

    // Get the image file path for the csv
    std::string csv_path = std::regex_replace(path, std::regex("\/(?:.(?!\/))+$"), "/data.csv");

    // Get the t value from path
    std::string t_value = std::regex_replace(path, std::regex(".*\/(.+)\.ppm"), "$1");
    qDebug() << csv_path.c_str();
    qDebug() << t_value.c_str();

    // Open the csv file
    csv.open(csv_path, std::ios_base::app);

    // If saving for the first time, add csv headers
    if (first_save)
    {
        csv << dimension << "," << b << "," << e << '\n';
        first_save = false;
    }

    if (img.is_open())
    { // proceed with output

        // Saving as ppm, adding the necessary headers
        img << "P3" << std::endl;
        img << dimension << " " << dimension << std::endl;
        img << "255" << std::endl;

        for (int i = 0; i < dimension; ++i)
        {
            for (int j = 0; j < dimension; ++j)
            {
                GeneticIndividual last_cell = old_lattice.at(i).at(j);

                // get the colour depending on the previous strategies
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

                // Save the fitness at t value
                csv << lattice.at(i).at(j).get_fitness() << "," << lattice.at(i).at(j).get_strategy() << "," << t_value << '\n';
            }
        }
        // Close all the files
        img.close();
        csv.close();
    }
    else
    {
        throw std::runtime_error("Could not open file");
    }
}

/**
 *
 * Change a strategy at i,j
 *
 * @brief GeneticLattice::change_lattice
 * @param i: row
 * @param j: column
 * @param c: strategy
 */
void GeneticLattice::change_lattice(int i, int j, char c)
{
    if (i >= get_dimension() || j >= get_dimension())
    {
        qDebug() << "Invalid lattice";
    }
    else
    {
       lattice.at(i).at(j).set_strategy(c);
    }
}
