//
//  simulated_annealing.hpp
//  join_ordering
//
//  Created by Irene Erlyn Wina Rachmawan on 2020/03/09.
//  Copyright © 2020 Irene - lynrc. All rights reserved.
//

#ifndef simulated_annealing_hpp
#define simulated_annealing_hpp

#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <tuple>
#include <random>
#include <ctime>
#include <algorithm>
#include <time.h>
#include "stats.h"

class simulated_annealing
{
public:
    std::vector<int> arr;
    int n;
    std::vector<TABLE> table_statistic;
    simulated_annealing( std::vector<int> arr_, int NRel, const std::vector<TABLE> stat){
        arr = arr_;
        n = NRel;
        table_statistic = stat;
    }
    double initiate_T = initiate_Temperature(arr, n);
    int join_cost_function(std::vector<int> trialSolution, int n);
    std::vector<int> new_solution (std::vector<int> arr, int n);
    std::tuple<std::vector<int>, int> annealing_process(std::vector<int> arr, double temp, int n);
    double initiate_Temperature(std::vector<int> arr, int n);
    std::tuple<std::vector<int>, int> getPlan_simulatedAnnealing();
    
};


#endif /* simulated_annealing_hpp */
