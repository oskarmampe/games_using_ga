#ifndef GENETICINDIVIDUAL_H
#define GENETICINDIVIDUAL_H
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <map>
#include <QDebug>
class GeneticIndividual
{
    // 0 cooperate 1 defect
public:
    enum ENCODING {CELLSTATE, ATTRIBUTE, AUTOMATA};
    GeneticIndividual(ENCODING);
    GeneticIndividual(ENCODING, char);
    //GeneticIndividual(bool*, ENCODING);
    double fitness_function(std::vector<char>, std::vector<std::vector<double>>);
    int get_gene_size();
    int get_random_number(int);
    char get_strategy();
    double get_fitness();
    ENCODING get_encoding();
    void set_strategy(char);
    void play(std::vector<char>, std::vector<std::vector<double>>);
    bool* genes;

private:
    void encode();
    void make_automata();
    void traverse_automata(std::vector<char>);
    int state;
    void initialise();
    std::map<int, std::map<int,int>> automata;
    char automata_values[2];
    ENCODING current;
    std::map<std::string, int> attributes;
    char strategy;
    int gene_size;
    double fitness;

};

#endif // GENETICINDIVIDUAL_H
