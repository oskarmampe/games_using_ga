#include "genetic_algorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int dimension, std::vector<std::vector<double>> payoff_matrix)
{
    //pop = new GeneticPopulation(10, 5);
    this->dimension = dimension;
    this->payoff_matrix = payoff_matrix;
    generation = 0;
}

std::vector<std::vector<GeneticIndividual>> GeneticAlgorithm::simulate(std::vector<std::vector<GeneticIndividual>> lattice)
{
    this->lattice = lattice;
    qDebug() << "SELECTION";
    selection();
    qDebug() << "CROSSOVER";
    crossover();

    if (rand() % 1000 + 1 == 7)
    {
        qDebug() << "MUTATION";
        mutation();
    }
    generation++;
    return this->lattice;
}

void GeneticAlgorithm::selection()
{
    std::vector<std::vector<GeneticIndividual>> current = lattice;
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            // Get the player index and strategy
            std::vector<int> player_idx = {i ,j};

            std::vector<std::vector<int>> neighbours = get_neighbours(player_idx);

            // Get all neighbour strategies
            std::vector<char> players;
            for (auto &idx : neighbours)
            {
                players.push_back(current[idx[0]][idx[1]].get_strategy());
            }

            // Get the payoff of the cell
            lattice[i][j].play(players, payoff_matrix);
        }
    }
}

void GeneticAlgorithm::mutation()
{

}

void GeneticAlgorithm::crossover()
{

}


/**
** Takes in a board of any square dimension, and gets all the neighbours of a cell.
** Cells around the edge are wrapped around to create a toroid like shape.
**/
std::vector<std::vector<int>> GeneticAlgorithm::get_neighbours(std::vector<int> index)
{
        std::vector<std::vector<int>> neighbours;


    // Create an array of the positions of neighbours relative to the current cell.
    // For example, (-1, -1) represents the neighbour that is 1 to the left and 1 down from the current cell.
    std::vector<std::vector<int>> neighbours_idx = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < neighbours_idx.size(); ++i)
    {
        std::vector<int> idx = neighbours_idx[i];
        // Put the row and col indices into a variable to check if they're on the boundary.
        int row = index[0] + idx[0];
        int col = index[1] + idx[1];

        // Wrap around to a torus-like structure by creating circular connections
        // For example, for a row, if there's no neighbour to the left, go to the last cell in that row.
        // Similar logic applies to columns.
        if (row < 0)
        {
            row = dimension-1;
        }
        else if (row > dimension-1)
        {
            row = 0;
        }

        if (col < 0)
        {
            col = dimension-1;
        }
        else if (col > dimension-1)
        {
            col = 0;
        }

        neighbours.push_back(std::vector<int>{row, col});
    }
        return neighbours;
}
