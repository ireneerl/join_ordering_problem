//  Created by Irene Erlyn Wina Rachmawan on 2020/03/02.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#ifndef greedy_hpp
#define greedy_hpp

#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <tuple>
#include "stats.h"

class greedy
{
public:
    std::vector<int> arr;
    int n;
    std::vector<TABLE> table_statistic;
    greedy( std::vector<int> arr_, int NRel, const std::vector<TABLE> stat){
        arr = arr_;
        n = NRel;
        table_statistic = stat;
    }
    std::tuple<int, int> initial_plan_generations(std::vector<int> arr, std::vector<int> data,  int start, int end,  int index, int r, int *total_size, int *total_join, std::vector<int> &greedy_solution);
    std::tuple<std::vector<int>, int> getPlan_greedy();
    std::vector<int> findRestoftheElement(std::vector<int> relations, std::vector<int> greddy_curr_solution, int n);
    std::tuple<int, int> greedy_move(std::vector<int> &greedy_solution, std::vector<int> rest, int n, int r, int size_join_res, int join_cost_res);

};

#endif /* greedy_hpp */
