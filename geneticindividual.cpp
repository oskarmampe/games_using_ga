#include "geneticindividual.h"

/**
 * Default constructor. It assumes the 2 strategy Prisonner's Dilemma of defector and cooperator.
 * @brief GeneticIndividual::GeneticIndividual
 * @param encoding
 *
 */
GeneticIndividual::GeneticIndividual(ENCODING encoding)
{
   this->current = encoding;
   this->strategy = 'c';
   initialise();
}

/**
 *
 * Alternative constructor, changes the default strategy
 *
 * @brief GeneticIndividual::GeneticIndividual
 * @param encoding
 * @param strategy
 */
GeneticIndividual::GeneticIndividual(GeneticIndividual::ENCODING encoding, char strategy)
{
    this->strategy = strategy;
    this->current = encoding;
    initialise();
}

/**
 *
 * Fitness function of the cell. For all encoding payoff value is a part of the fitness.
 *
 * @brief GeneticIndividual::fitness_function
 * @param neighbours
 * @param payoff_matrix
 * @return
 */
double GeneticIndividual::fitness_function(std::vector<char> neighbours, std::vector<std::vector<double>> payoff_matrix)
{
    // Play a game with neighbours, and get payoff value
    int player_strat = get_strategy() == 'c' ? 0 : 1;
    long double result = 0.0;
    for (auto &neighbour : neighbours)
    {
        int enemy_strat = neighbour == 'c' ? 0 : 1;
        result += payoff_matrix[player_strat][enemy_strat];
    }

    // Based on the different encoding, add to the fitness value.
    if (current == GeneticIndividual::CELLSTATE)
    {
        // Get all strategies, including previous ones
        int player_strats[3] = {player_strat, (int)genes[get_gene_size()-1], (int)genes[get_gene_size()-2]};
        // Play with the 'history' of cells for each previous strategy and the current one.
        for (int i = 1; i < get_gene_size()-2; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                result += payoff_matrix[player_strats[j]][(size_t)genes[i]];
            }
        }
    }
    else if (current == GeneticIndividual::ATTRIBUTE)
    {
        int aggr;
        int def;

        aggr |= genes[get_gene_size()-6] << 3;
        aggr |= genes[get_gene_size()-5] << 2;
        aggr |= genes[get_gene_size()-4] << 1;

        def |= genes[get_gene_size()-3] << 3;
        def |= genes[get_gene_size()-2] << 2;
        def |= genes[get_gene_size()-1] << 1;


        // Divide the coefficient by 10, as fitness values can be high in value, thus reducing accuracy.
        int player_strats[3] = {player_strat, (int)genes[get_gene_size()-7], (int)genes[get_gene_size()-8]};
        // Play with the 'history' of cells for each previous strategy and the current one. Also multiply aggressiveness/defensiveness as a coefficient
        for (int i = 1; i < get_gene_size()-8; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                int coeff = genes[i] == false ? aggr : def;
                result += (double(coeff)/10)*payoff_matrix[player_strats[j]][(size_t)genes[i]];
            }
        }
    }

    return result;
}

/**
 *
 * Gene size getter
 *
 * @brief GeneticIndividual::get_gene_size
 * @return gene size
 */
int GeneticIndividual::get_gene_size()
{
    return gene_size;
}

/**
 *
 * Strategy setter
 *
 * @brief GeneticIndividual::set_strategy
 */
void GeneticIndividual::set_strategy(char strategy)
{
    this->strategy = strategy;
    initialise();
}

/**
 *
 *  Encode the strategy through genes
 *
 * @brief GeneticIndividual::encode
 */
void GeneticIndividual::encode(){
    if (this->current == CELLSTATE)
    {
        // current strategy previous 2 strategies of 8 neighbours + 2 previous strategies of the cell
        gene_size = 1+8*2+2*2;
        genes = new bool[gene_size];
        for (int i = 0; i < get_gene_size(); ++i)
        {
            genes[i] = get_random_int(0, 1) == 0 ? false : true;
        }
    }
    else if (this->current == ATTRIBUTE)
    {
        // current strategy previous 2 strategies of 8 neighbours + 2 previous strategies of the cell + 2 attributes
        gene_size = 1+8*2+2*2+3*2;
        genes = new bool[gene_size];
        for (int i = 0; i < get_gene_size(); ++i)
        {
            genes[i] = get_random_int(0, 1) == 0 ? false : true;
        }
    }
    else if (this->current == AUTOMATA)
    {
        //current strategy 1 initial state, 2 current strategies, 4 moves to another state
        gene_size = 1+2*3;

        // Cooperate and defect strategies as automata.
        bool cooperate[]{false, false, false, false, true, true, true};
        bool defect[]{true, true, true, true, true, false, false};

        if (this->strategy == 'd')
        {
            genes = defect;
        }
        else if(this->strategy == 'c')
        {
            genes = cooperate;
        }
        else
        {
            genes = cooperate;
        }
    }
}

/**
 *
 * Make automata from the genes.
 *
 * @brief GeneticIndividual::make_automata
 */
void GeneticIndividual::make_automata()
{
    // Get the initial state and clear everything
    int initial_state = genes[0] == false ? 0 : 1;
    state = initial_state;
    int other_state = initial_state == 1 ? 0 : 1;
    automata.clear();

    // Where to go from the initial state
    std::map<int, int> initial_inner;
    initial_inner.insert(std::make_pair(0, genes[2] == false ? 0 : 1));
    initial_inner.insert(std::make_pair(1, genes[3] == false ? 0 : 1));
    automata.insert(std::make_pair(initial_state, initial_inner));

    // Where to go from the other state
    std::map<int, int> other_inner;
    other_inner.insert(std::make_pair(0, genes[5] == false ? 0 : 1));
    other_inner.insert(std::make_pair(1, genes[6] == false ? 0 : 1));
    automata.insert(std::make_pair(other_state, other_inner));

    // Get the strategies at each state
    automata_values[initial_state] = genes[1] == false ? 'c' : 'd';
    automata_values[other_state] = genes[4] == false ? 'c' : 'd';
}

/**
 *
 * Traverse the automata for each neighbour played with
 *
 * @brief GeneticIndividual::traverse_automata
 * @param neighbours
 */
void GeneticIndividual::traverse_automata(std::vector<char> neighbours)
{
    for (int i = 0; i < neighbours.size(); ++i)
    {
        int transition = neighbours[i] == 'c' ? 0 : 1;
        state = automata[state][transition];
    }
}

/**
 *
 * Initialise the individual; used to construct.
 *
 * @brief GeneticIndividual::initialise
 */
void GeneticIndividual::initialise()
{
    encode();// encode the genes

    if(this->current == ATTRIBUTE)
    {
        genes[0] = this->strategy == 'c' ? 0 : 1;
    }
    else if (this->current == AUTOMATA)
    {
        make_automata();
    }
    else if (this->current == CELLSTATE)
    {
        genes[0] = this->strategy == 'c' ? 0 : 1;
    }
}

/**
 *
 * Play with the neighbours, and update the genes.
 *
 * @brief GeneticIndividual::play
 * @param neighbours
 * @param payoff_matrix
 */

void GeneticIndividual::play(std::vector<char> neighbours, std::vector<std::vector<double>> payoff_matrix)
{
    fitness = fitness_function(neighbours, payoff_matrix);
    if (this->current == CELLSTATE)
    {
        // move every gene by 1
        for (int i = get_gene_size()-2; i > 0; --i) {
            genes[i+1] = genes[i];
        }

        // Change the leftmost neighbour to be the most recent one
        int c = 1;
        for (auto& neighbour : neighbours)
        {
            genes[c] = neighbour == 'c' ? 0 : 1;
            c += 2;
        }

        // Save the last strategy played
        genes[get_gene_size()-2] = strategy;

    }
    else if (this->current == ATTRIBUTE)
    {
        // move every gene by 1
        // get_gene_size()-8 as gene_size-1 would be the last element,
        // so need to start at gene_size-2 to move it to gene_size-1
        // attribute also contains 6 bits for attributes so don't count those
        for (int i = get_gene_size()-8; i > 0; --i) {
            genes[i+1] = genes[i];
        }

        // Change the leftmost neighbour to be the most recent one
        int c = 1;
        for (auto& neighbour : neighbours)
        {
            genes[c] = neighbour == 'c' ? 0 : 1;
            c += 2;
        }
    }
    else if (this->current == AUTOMATA)
    {
        traverse_automata(neighbours);
    }
}

/**
 *
 * Strategy getter
 *
 * @brief GeneticIndividual::get_strategy
 * @return strategy
 */

char GeneticIndividual::get_strategy()
{
    if (this->current == CELLSTATE)
    {
        return genes[0] == false ? 'c' : 'd';
    }
    else if (this->current == ATTRIBUTE)
    {
        return genes[0] == false ? 'c' : 'd';
    }
    else if (this->current == AUTOMATA)
    {
        return automata_values[state];
    }
}

/**
 *
 * Fitness value getter
 *
 * @brief GeneticIndividual::get_fitness
 * @return saved fitness value
 */
double GeneticIndividual::get_fitness()
{
    return fitness;
}

/**
 *
 * Encoding getter
 *
 * @brief GeneticIndividual::get_encoding
 * @return
 */
GeneticIndividual::ENCODING GeneticIndividual::get_encoding()
{
    return current;
}

/**
 *
 * Get a random int from an uniform distribution
 *
 * @brief GeneticIndividual::get_random_int
 * @param min: minimum value to get
 * @param max: maximum vaule to get
 * @return random int
 */
int GeneticIndividual::get_random_int(int min, int max)
{
    std::uniform_int_distribution<> dist(min, max);

    return dist(engine);
}
