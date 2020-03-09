//  Created by Irene Erlyn Wina Rachmawan on 2020/02/28.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#ifndef brute_force_h
#define brute_force_h

#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <tuple>
#include "stats.h"

class brute_force
{
public:
    std::vector<int> arr;
    int n;
    std::vector<TABLE> table_statistic;
    brute_force( std::vector<int> arr_, int NRel, const std::vector<TABLE> stat){
        arr = arr_;
        n = NRel;
        table_statistic = stat;
    }
    std::tuple<std::vector<int>, int> plan_generations(std::vector<int> arr, int index, int n, int minimum_total_join);
    std::tuple<std::vector<int>, int> getPlan_bruteForce();
    
};

#endif /* brute_force_hpp */
