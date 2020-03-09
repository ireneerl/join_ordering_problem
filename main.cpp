//  Created by Irene Erlyn Wina Rachmawan on 2020/03/02.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <tuple>
#include "incl/stats.h"
#include "incl/brute_force.h"
#include "incl/greedy.hpp"
#include "incl/dynamic_programming.hpp"
#include "incl/genetic_algorithm.hpp"
#include "incl/simulated_annealing.hpp"

#define N_rel 4

std::vector<TABLE> table_statistic; //definition

void initialize(){
    table_statistic.push_back({'R', 1000, {100,200,-1,-1}});
    table_statistic.push_back({'S', 1000, {-1,100,500,-1}});
    table_statistic.push_back({'T', 1000, {-1,-1,20,50}});
    table_statistic.push_back({'U', 1000, {50,-1,-1,1000}});
}

std::vector<TABLE> get_table_stats(int n){
    initialize();
    return table_statistic;
}

std::vector<int> get_initial_plan(int n){
    std::vector<int> arr(n); // vector with 100 ints.
    std::iota (std::begin(arr), std::end(arr), 1); // Fill with 0, 1, ..., N_rel
    return arr;
}

int main(){
    get_table_stats(N_rel);
    std::vector<int> arr = get_initial_plan(N_rel);
    int minimum_total_join;
    std::vector<int> path;
    
    std::cout << "calculating ..";
    
    
//    std::cout << std::endl << " .. Brute Force .." << std::endl ;
//    brute_force BF(arr, N_rel, table_statistic);
//    minimum_total_join = 0;
//    std::tie(path, minimum_total_join) = BF.getPlan_bruteForce();
//    std::cout << "RESULT FROM BRUTE FORCE" << std::endl;
//    for(int i = 0 ; i < path.size() ; i++)
//        std::cout << path[i];
//    std::cout << std::endl << minimum_total_join <<std::endl;
//
//    std::cout << std::endl << " .. Greedy .." << std::endl ;
//    greedy greedy(arr, N_rel, table_statistic);
//    minimum_total_join = 0;
//    std::tie(path, minimum_total_join) = greedy.getPlan_greedy();
//    std::cout << "RESULT GREEDY" << std::endl;
//    for(int i = 0 ; i < path.size() ; i++)
//        std::cout << path[i];
//    std::cout << std::endl << minimum_total_join <<std::endl;
//    
//    std::cout << std::endl << " .. Dynamic Programming .." << std::endl ;
//    dynamic_programming DP(arr, N_rel, table_statistic);
//    minimum_total_join = 0;
//    std::tie(path, minimum_total_join) = DP.getPlan_dynamicProgramming();
//    std::cout << "RESULT DP" << std::endl;
//    for(int i = 0 ; i < path.size() ; i++)
//        std::cout << path[i];
//    std::cout << std::endl << minimum_total_join <<std::endl;
//
//    std::cout << std::endl << " .. Genetic Algorithm .." << std::endl ;
//    genetic_algorithm GA(arr, N_rel, table_statistic, 3);
//    minimum_total_join = 0;
//    std::tie(path, minimum_total_join) = GA.getPlan_geneticAlgorithm();
//    std::cout << "RESULT GA" << std::endl;
//    for(int i = 0 ; i < path.size() ; i++)
//        std::cout << path[i];
//    std::cout << std::endl << minimum_total_join <<std::endl;
    
    std::cout << std::endl << " .. Simulated Annealing .." << std::endl ;
    simulated_annealing SA(arr, N_rel, table_statistic);
    minimum_total_join = 0;
    std::tie(path, minimum_total_join) = SA.getPlan_simulatedAnnealing();
    std::cout << "RESULT SA" << std::endl;
    for(int i = 0 ; i < path.size() ; i++)
        std::cout << path[i];
    std::cout << std::endl << minimum_total_join <<std::endl;
    
    return 0;
}
