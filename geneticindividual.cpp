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
   initialise();
}

GeneticIndividual::GeneticIndividual(GeneticIndividual::ENCODING encoding, char strategy)
{
    this->strategy = strategy;
    this->current = encoding;
    initialise();
}

//GeneticIndividual::GeneticIndividual(bool* genes, ENCODING encoding)
//{
//    this->genes = genes;
//}

double GeneticIndividual::fitness_function(std::vector<char> neighbours, std::vector<std::vector<double>> payoff_matrix)
{
    int player_strat = get_strategy() == 'c' ? 0 : 1;
    double result = 0;
    for (auto &neighbour : neighbours)
    {
        int enemy_strat = neighbour == 'c' ? 0 : 1;
        result += payoff_matrix[player_strat][enemy_strat];
    }

    if (current == GeneticIndividual::CELLSTATE)
    {
        for (int i = 1; i < get_gene_size(); ++i)
        {
            result += payoff_matrix[player_strat][(size_t)genes[i]];
        }
    }
    else if (current == GeneticIndividual::ATTRIBUTE)
    {
        for (int i = 1; i < get_gene_size()-6; ++i)
        {
            result += payoff_matrix[player_strat][(size_t)genes[i]];
        }
    }

    return result;
}

int GeneticIndividual::get_gene_size()
{
    return gene_size;
}

void GeneticIndividual::set_strategy(char strategy)
{
    this->strategy = strategy;
    initialise();
}

void GeneticIndividual::encode(){
    static std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<> dist(0, 1);
    if (this->current == CELLSTATE)
    {
        // current strategy previous 2 strategies of 8 neighbours + 2 previous strategies of the cell
        gene_size = 1+8*2+2*2;
        genes = new bool[gene_size];
        for (int i = 0; i < get_gene_size(); ++i)
        {
            genes[i] = dist(engine) == 0 ? false : true;
        }
    }
    else if (this->current == ATTRIBUTE)
    {
        // current strategy previous 2 strategies of 8 neighbours + 2 previous strategies of the cell + 2 attributes
        gene_size = 1+8*2+2*2+3*2;
        genes = new bool[gene_size];
        for (int i = 0; i < get_gene_size(); ++i)
        {
            genes[i] = dist(engine) == 0 ? false : true;
        }
    }
    else if (this->current == AUTOMATA)
    {
        //current strategy 1 initial state, 2 current strategies, 4 moves to another state
        gene_size = 1+2*2+4*2;
        genes = new bool[gene_size];
        bool cooperate[]{false, false, false, false, true, true, true};
        bool defect[]{true, true, true, true, false, false, false};
        //bool tft[]{false, false, false, true, true, false, true};
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

void GeneticIndividual::make_automata()
{
    int initial_state = (int)genes[0];
    state = initial_state;
    automata.clear();

    std::map<int, int> initial_inner;
    initial_inner.insert(std::make_pair(0, (int)genes[2]));
    initial_inner.insert(std::make_pair(1, (int)genes[3]));
    automata.insert(std::make_pair(initial_state, initial_inner));

    std::map<int, int> other_inner;
    other_inner.insert(std::make_pair(0, (int)genes[5]));
    other_inner.insert(std::make_pair(1, (int)genes[6]));
    automata.insert(std::make_pair(!genes[0], other_inner));
    automata_values[initial_state] = genes[1] == false ? 'c' : 'd';
    automata_values[(int)!genes[0]] = genes[4] == false ? 'c' : 'd';

    if (get_strategy() == 'd')
    {
        qDebug() << "(int)!genes[0]" << QString::number((int)!genes[0]);
        qDebug() << "Initial State: " << QString::number(initial_state);
        for (auto it = automata.cbegin(); it != automata.cend(); ++it)
        {
            qDebug() << "First" << it->first;

            for (auto it1 = it->second.cbegin(); it1 != it->second.cend(); ++it1)
            {
                qDebug() << "First First" << it1->first;
                qDebug() << "First Second" << it1->first;
            }
        }
    }
}

void GeneticIndividual::traverse_automata(std::vector<char> neighbours)
{
    for (int i = 0; i < neighbours.size(); ++i)
    {
        int transition = neighbours[i] == 'c' ? 0 : 1;
        state = automata[state][transition];
    }
}

void GeneticIndividual::initialise()
{
    encode();
    static std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<> dist(0, 4);
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

void GeneticIndividual::play(std::vector<char> neighbours, std::vector<std::vector<double>> payoff_matrix)
{
    fitness = fitness_function(neighbours, payoff_matrix);
  //  qDebug() << QString::number(fitness);
    if (this->current == CELLSTATE)
    {
        // update genes
        int c = 1;
        for (auto& neighbour : neighbours)
        {
            genes[c] = neighbour == 'c' ? 0 : 1;
            c += 2;
        }

    }
    else if (this->current == ATTRIBUTE)
    {
        for (int i = get_gene_size()-1; i > 0; --i) {
            genes[i+1] = genes[i];
        }

        int c = 1;
        for (auto& neighbour : neighbours)
        {
            genes[c] = neighbour == 'c' ? 0 : 1;
            c += 2;
        }
        int aggr;
        int def;

        aggr |= genes[get_gene_size()-6] << 3;
        aggr |= genes[get_gene_size()-5] << 2;
        aggr |= genes[get_gene_size()-4] << 1;

        def |= genes[get_gene_size()-3] << 3;
        def |= genes[get_gene_size()-2] << 2;
        def |= genes[get_gene_size()-1] << 1;

        if (aggr >= 4)
        {
            genes[0] = true;
        }
        else if (def >= 4)
        {
            genes[0] = false;
        }
    }
    else if (this->current == AUTOMATA)
    {
        traverse_automata(neighbours);
    }
}

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

double GeneticIndividual::get_fitness()
{
    return fitness;
}

GeneticIndividual::ENCODING GeneticIndividual::get_encoding()
{
    return current;
}




