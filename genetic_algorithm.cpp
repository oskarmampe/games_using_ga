#include "genetic_algorithm.h"

/**
 *
 * Constructor
 *
 * @brief GeneticAlgorithm::GeneticAlgorithm
 */
GeneticAlgorithm::GeneticAlgorithm()
{
    generation = 0;
}

/**
 * @brief GeneticAlgorithm::simulate
 * @param dimension
 * @param payoff_matrix
 * @param lattice: lattice of GeneticIndividuals
 * @param global_pop: global or local/neighbourhood
 * @param parent_num: number of parents
 * @param child_num: number of children
 * @param mut: mutation on or off
 * @return
 */
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
 * Loop around neighbourhood/global lattice
 * Sort every individual by fitness
 * Replace children with parents
 * Mutation if turned on
 *
 * @brief GeneticAlgorithm::selection
 * @param global_pop: global or local/neighbourhood
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

/**
 *
 * One of the possible populations. Loops around the neighbourhood, gets the best parents, and performs crossover/mutation
 *
 * @brief GeneticAlgorithm::neighbourhood_pop
 */
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

            // Check if number of parents is not higher than dimension
            int loop_num = parent_num <= players.size() && parent_num > 0 ? parent_num : players.size();

            // Get all fitness values of individuals
            for (int i  = 0; i < loop_num; ++i)
            {
                fitness_values.push_back(players.at(i).get_fitness());
            }

            // Get all parents
            std::vector<GeneticIndividual> parents;
            for (int i  = 0; i < loop_num; ++i)
            {
                parents.push_back(players.at(get_random_distribution(fitness_values.begin(), fitness_values.end())));
            }

            // Perform genetic operators
            lattice.at(i).at(j) = crossover(parents);
            if (mut)
            {
                 mutation(lattice.at(i).at(j));
            }
        }
    }
}

/**
 *
 * Get a random number from a distribution
 *
 * @brief GeneticAlgorithm::get_random_distribution
 * @param first: first element of an vector
 * @param last: last element of a vector
 * @return random number
 */
int GeneticAlgorithm::get_random_distribution(std::vector<double>::iterator first, std::vector<double>::iterator last)
{
    std::discrete_distribution<> dist(first, last); // Create the distribution
    return dist(engine);
}

/**
 *
 * Get a random number from a uniform distribution
 *
 * @brief GeneticAlgorithm::get_random_int
 * @param min: minimum value to get
 * @param max: maximum value to get
 * @return random number
 */
int GeneticAlgorithm::get_random_int(int min, int max)
{
    std::uniform_int_distribution<> dist(min, max);
    return dist(engine);
}

/**
 *
 * One of the possible populations. Loops around the neighbourhood, gets the best parents, and performs crossover/mutation
 *
 * @brief GeneticAlgorithm::one_lattice_pop
 */
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

    // Check if parents is higher than dimension
    int loop_num = parent_num <= players.size() && parent_num > 0 ? parent_num : players.size();

    // Get the fitness values of all individuals
    for (int i  = 0; i < loop_num; ++i)
    {
        fitness_values.push_back(std::get<1>(players.at(i)).get_fitness());
    }

    // Get best parents and perform genetic operators
    for (int i = 0; i < child_num; ++i)
    {
        std::vector<int> idx = std::get<0>(players.at(players.size()-i-1));
        std::vector<GeneticIndividual> parents;

        // Get parents based on a discrete distribution
        parents.push_back(std::get<1>(players.at(get_random_distribution(fitness_values.begin(), fitness_values.end()))));
        parents.push_back(std::get<1>(players.at(get_random_distribution(fitness_values.begin(), fitness_values.end()))));

        // perform genetic operators
        lattice.at(idx[0]).at(idx[1]) = crossover(parents);
        if (mut)
        {
            mutation(lattice.at(idx[0]).at(idx[1]));
        }
    }
}

/**
 *
 * Perform mutation operator.
 *
 * @brief GeneticAlgorithm::mutation
 * @param ind
 */
void GeneticAlgorithm::mutation(GeneticIndividual ind)
{
    if (get_random_int(0, 100000) == 7)
    {
        int random_number = get_random_int(0, ind.get_gene_size()-1);
        ind.genes[random_number] = !ind.genes[random_number];
    }
}

/**
 *
 * Perform fifty-fifty crossover operator.
 *
 * @brief GeneticAlgorithm::crossover
 * @param parents: array of possible parents.
 * @return new child
 */
GeneticIndividual GeneticAlgorithm::crossover(std::vector<GeneticIndividual> parents)
{
    std::vector<GeneticIndividual> two_parents;
    int index1 = get_random_int(0, parents.size()-1);
    int index2;

    // Check if two indexes aren't the same
    while (true)
    {
        index2 = get_random_int(0, parents.size()-1);
        if(index2 != index1)
        {
            break;
        }
    }

    two_parents.push_back(parents.at(index1));
    two_parents.push_back(parents.at(index2));

    // Get a random parent and duplicate it as a child
    if (two_parents.at(0).get_encoding() == GeneticIndividual::AUTOMATA)
    {
        return get_random_int(0, 1) == 0 ? two_parents.at(0) : two_parents.at(1);
    }
    else if (two_parents.at(0).get_encoding() == GeneticIndividual::CELLSTATE)
    {
        return get_random_int(0, 1) == 0 ? two_parents.at(0) : two_parents.at(1);
    }
    else if (two_parents.at(0).get_encoding() == GeneticIndividual::ATTRIBUTE)
    {
        return get_random_int(0, 1) == 0 ? two_parents.at(0) : two_parents.at(1);
    }
}


/**
 *
 * Takes in a board of any square dimension, and gets all the neighbours of a cell.
 * Cells around the edge are wrapped around to create a toroid like shape.
 *
 * @brief GeneticAlgorithm::get_neighbours
 * @param index: vector of indices
 * @return a vector of neighbour indices
 */
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

