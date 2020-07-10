#include "lattice.h"

Lattice::Lattice(int dim, std::vector<std::vector<double>> &payoff) 
{
    dimension = dim;
    payoff_matrix = payoff;

    for (int i = 0; i < dimension; ++i)
    {
        std::vector<char> temp;

        for (int j = 0; j < dimension; ++j)
        {
            temp.push_back('c');
        }
        lattice.push_back(temp);
    }

    lattice[(int)((dimension-1)/2)][(int)((dimension-1)/2)] = 'd';

}

Lattice::~Lattice()
{
}

/**
** Takes in a board of any square dimension, and gets all the neighbours of a cell.
** Cells around the edge are wrapped around to create a toroid like shape.
**/
std::vector<std::vector<int>> Lattice::get_neighbours(std::vector<int> index)
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

/**
** Play the spatial game with the cell's neighbours. Currently, only cooperator/defector strategy is used.
**/
double Lattice::play_with_neighbours(char player, std::vector<char> neighbours)
{
        int player_strat = player == 'c' ? 0 : 1;
    double result = 0;
    for (auto &neighbour : neighbours)
    {
        int enemy_strat = neighbour == 'c' ? 0 : 1;
        result += payoff_matrix[player_strat][enemy_strat];
    }

    return result;
}

/**
** Create a new board, but along with the cell's strategy, it's payoff value is also recorded.
**/
std::vector<std::vector<std::tuple<char, double>>> Lattice::get_payoff_values()
{
        // Preload an array with tuples representing the strategy and it's payoff. 
    std::vector<std::vector<std::tuple<char, double>>> payoff_board;
    for (int i = 0; i < dimension; ++i)
    {
        std::vector<std::tuple<char, double>> temp;
        for (int j = 0; j < dimension; ++j)
        {
            temp.push_back(std::tuple<char, double>{'-', -9999.9});
        }
        payoff_board.push_back(temp);
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            // Get the player index and strategy
            std::vector<int> player_idx = {i ,j};
            char player = lattice[i][j];
            // Get all the neighbours indices
            std::vector<std::vector<int>> neighbours = get_neighbours(player_idx);
            // Get all neighbour strategies
            std::vector<char> players;
            for (auto &idx : neighbours)
            {
                players.push_back(lattice[idx[0]][idx[1]]);
            } 
            // Get the payoff of the cell
            double cell_sum = play_with_neighbours(player, players);
            payoff_board[i][j] = std::tuple<char, double>{lattice[i][j], cell_sum};
        }
    }

    return payoff_board;
}

/**
** Update the board, which requires a board with the strategies and payoffs.
**/
std::vector<std::vector<char>> Lattice::update(std::vector<std::vector<std::tuple<char, double>>> payoff_board)
{
        std::vector<std::vector<char>> new_board;
    for (int i = 0; i < dimension; ++i)
    {
        std::vector<char> temp;
        for (int j = 0; j < dimension; ++j)
        {
            temp.push_back('-');
        }
        new_board.push_back(temp);
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            // Get the cell index and strategy & payoff
            std::vector<int> player_idx{i, j};
            std::tuple<char, double> player = payoff_board[i][j];
            char strat = std::get<0>(player);
            double payoff = std::get<1>(player);
            // Get all of the neighbours
            std::vector<std::vector<int>> neighbours = get_neighbours(player_idx);
            
            // Loop around all the neighbours and find the maximum of the neighbours
            double best_payoff = payoff;
            char best_strat = strat;
            for (auto &neighbour : neighbours)
            {
                std::tuple<char, double> neigh = payoff_board[neighbour[0]][neighbour[1]];
                char neigh_strat = std::get<0>(neigh);
                double neigh_payoff = std::get<1>(neigh);
                if (neigh_payoff > best_payoff)
                {
                    best_strat = neigh_strat;
                    best_payoff = neigh_payoff;
                }
            }
            new_board[i][j] = payoff > best_payoff ? strat : best_strat;
        }
    }
    return new_board;
}


void Lattice::simulate(const int t)
{
    for (int i = 0; i < t; ++i)
    {
        std::cout << "-------------------------------------" << "BEGINNING OF T: " << i << "-------------------------------------" << std::endl;
        old_lattice = lattice;
        std::vector<std::vector<std::tuple<char, double>>> payoff_board = get_payoff_values();
        lattice = update(payoff_board);
        std::cout << "-------------------------------------" << "END OF T: " << i << "-------------------------------------" << std::endl;
    }
}

void Lattice::print_lattice()
{
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            std::cout << lattice[i][j] << " ";
        }
        std::cout << std::endl;
    }
}