//  Created by Irene Erlyn Wina Rachmawan on 2020/03/09.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#ifndef genetic_algorithm_hpp
#define genetic_algorithm_hpp

#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <tuple>
#include <random>
#include <ctime>
#include <algorithm>
#include "stats.h"

struct INDVI{
    std::vector <int> gens ;
    double fitness_val;
    double probability;
    //only for memory ->
    int size;
    int cost;
};

class genetic_algorithm
{
public:
    std::vector<int> arr;
    int n, Nevolution;
    std::vector<TABLE> table_statistic;
    genetic_algorithm( std::vector<int> arr_, int NRel, const std::vector<TABLE> stat, int evol){
        arr = arr_;
        n = NRel;
        table_statistic = stat;
        Nevolution = evol;
    }
    std::vector<INDVI> population;
    std::vector<INDVI> parents;
    std::vector<INDVI> children;
    
    std::tuple<std::vector<int>, int> getPlan_geneticAlgorithm();    
    void printPopulation(std::vector<INDVI> comm);
    void generate_population(std::vector<int> arr, int NRel, int NIndiv);
    void fitness_function(int N_indv, int n);
    void select_parents(int NIndiv, int NRel);
    void crossOver(double prob, int n);
    void mutation(double prob, int nrel);
    bool compareByFitnessValue(const INDVI &a, const INDVI &b);
};

#endif /* genetic_algorithm_hpp */
