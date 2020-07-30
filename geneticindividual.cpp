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

    return result;
}

int GeneticIndividual::get_gene_size()
{
    return gene_size;
}

int GeneticIndividual::get_random_number(int max)
{

    return rand() % max + 1;

}

void GeneticIndividual::set_strategy(char strategy)
{
    this->strategy = strategy;
    initialise();
}

void GeneticIndividual::encode(){
    if (this->current == CELLSTATE)
    {
        // current strategy previous 2 strategies of 8 neighbours + 2 previous strategies of the cell
        gene_size = 1+8*2+2*2;
        genes = new bool[gene_size];
        for (int i = 0; i < get_gene_size(); ++i)
        {
            genes[i] = get_random_number(10) <= 5 ? false : true;
        }
    }
    else if (this->current == ATTRIBUTE)
    {
        // current strategy previous 2 strategies of 8 neighbours + 2 previous strategies of the cell + 3 attributes
        gene_size = 1+8*2+2*2+2*3;
        genes = new bool[gene_size];
        for (int i = 0; i < get_gene_size(); ++i)
        {
            genes[i] = get_random_number(10) <= 5 ? false : true;
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

    if (this->strategy == 'd')
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
    if(this->current == ATTRIBUTE)
    {
        attributes.insert(std::pair<std::string, int>("aggressiveness", get_random_number(4)));
        attributes.insert(std::pair<std::string, int>("deffensive", get_random_number(4)));
    }
    else if (this->current == AUTOMATA)
    {
        make_automata();
    }
}

void GeneticIndividual::play(std::vector<char> neighbours, std::vector<std::vector<double>> payoff_matrix)
{
    fitness = fitness_function(neighbours, payoff_matrix);
    qDebug() << QString::number(fitness);
    if (this->current == CELLSTATE)
    {
        // update genes
        if (fitness < 8)
        {
            this->strategy = this->strategy == 'c' ? 'd' : 'c';
        }
    }
    else if (this->current == ATTRIBUTE)
    {
        if (fitness < 8 && attributes["aggressive"] > 5)
        {
            this->strategy = 'd';
        }
        else if (fitness < 8 && attributes["defensive"] > 5)
        {
            this->strategy = 'c';
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




