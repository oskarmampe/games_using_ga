#include "genetic_algorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
    generation = 0;
}

std::vector<std::vector<GeneticIndividual>> GeneticAlgorithm::simulate(int dimension, std::vector<std::vector<double>> payoff_matrix, std::vector<std::vector<GeneticIndividual>> lattice, bool global_pop, int parent_num, int child_num, bool mut)
{
    this->dimension = dimension;
    this->payoff_matrix = payoff_matrix;
    this->parent_num = parent_num;
    this->child_num = child_num;
    this->lattice = lattice;
    this->mut = mut;

    selection(global_pop);


    generation++;
    return this->lattice;
}

/**
 *
 * LOOP AROUND NEIGHBOURHOOD
 * SORT EVERYONE BY FITNESS
 * REMOVE 2, SELECT 4 RANDOM PARENTS TO MAKE 2
 * MUTATE THEM
 *
 * @brief GeneticAlgorithm::selection
 */
void GeneticAlgorithm::selection(bool global_pop)
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
    if (global_pop)
    {
        one_lattice_pop();
    }
    else
    {
        neighbourhood_pop();
    }
}


void GeneticAlgorithm::neighbourhood_pop()
{

    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            // Get the player index and strategy
            std::vector<int> player_idx = {i ,j};

            std::vector<std::vector<int>> neighbours = get_neighbours(player_idx);

            // Get all neighbour strategies
            std::vector<GeneticIndividual> players;
            for (auto &idx : neighbours)
            {
                players.push_back(lattice[idx[0]][idx[1]]);
            }
            players.push_back(lattice[i][j]);

            // Get the payoff of the cell
            std::sort(players.begin(), players.end(), compare);

            std::vector<double> fitness_values;

            int loop_num = parent_num <= players.size() && parent_num > 0 ? parent_num : players.size();

            for (int i  = 0; i < loop_num; ++i)
            {
                fitness_values.push_back(players.at(i).get_fitness());
            }

            // Get random number
            static std::random_device device;
            std::mt19937 engine(device()); // Seed the random number engine
            std::discrete_distribution<> dist(fitness_values.begin(), fitness_values.end()); // Create the distribution

            std::vector<GeneticIndividual> parents;
            for (int i  = 0; i < loop_num; ++i)
            {
                parents.push_back(players.at(dist(engine)));
            }
            lattice.at(i).at(j) = crossover(parents);
            if (mut)
            {
                 mutation(lattice.at(i).at(j));
            }
        }
    }
}

void GeneticAlgorithm::one_lattice_pop()
{
    std::vector<std::tuple<std::vector<int>, GeneticIndividual>> players;
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            // Get the player index and strategy
            std::vector<int> player_idx = {i ,j};

            players.push_back(std::make_tuple(player_idx, lattice[i][j]));
        }
    }
    // Get the payoff of the cell
    std::sort(players.begin(), players.end(), compare_tuple);

    std::vector<double> fitness_values;

    //qDebug() << "Players size" << QString::number(players.size());

    int loop_num = parent_num <= players.size() && parent_num > 0 ? parent_num : players.size();

    for (int i  = 0; i < loop_num; ++i)
    {
        fitness_values.push_back(std::get<1>(players.at(i)).get_fitness());
    }

    // Get random number
    static std::random_device device;
    std::mt19937 engine(device()); // Seed the random number engine
    std::discrete_distribution<> dist(fitness_values.begin(), fitness_values.end()); // Create the distribution

    //qDebug() << "Players size";

    for (int i = 0; i < child_num; ++i)
    {
        std::vector<int> idx = std::get<0>(players.at(players.size()-i-1));

        //qDebug() << "Index size" << QString::number(idx.size());

        std::vector<GeneticIndividual> parents;
        parents.push_back(std::get<1>(players.at(dist(engine))));
        parents.push_back(std::get<1>(players.at(dist(engine))));
        lattice.at(idx[0]).at(idx[1]) = crossover(parents);
        if (mut)
        {
            mutation(lattice.at(idx[0]).at(idx[1]));
        }
    }

        //qDebug() << "PlayersEND size";
}

void GeneticAlgorithm::mutation(GeneticIndividual ind)
{
    static std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<> dist(0, 10000);

    if (dist(engine) == 7)
    {
        static std::random_device dev;
        std::mt19937 eng(dev());
        std::uniform_int_distribution<> dis(0, ind.get_gene_size()-1);
        ind.genes[dis(eng)] = !ind.genes[dis(eng)];
    }

}

GeneticIndividual GeneticAlgorithm::crossover(std::vector<GeneticIndividual> parents)
{
    static std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<> dist(0, 1);

    if (parents.at(0).get_encoding() == GeneticIndividual::AUTOMATA)
    {
        return dist(engine) == 0 ? parents.at(0) : parents.at(1);
    }
    else if (parents.at(0).get_encoding() == GeneticIndividual::CELLSTATE)
    {
        return dist(engine) == 0 ? parents.at(0) : parents.at(1);
    }
    else if (parents.at(0).get_encoding() == GeneticIndividual::ATTRIBUTE)
    {
        return dist(engine) == 0 ? parents.at(0) : parents.at(1);
    }
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

