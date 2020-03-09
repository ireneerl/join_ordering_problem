//  Created by Irene Erlyn Wina Rachmawan on 2020/03/03.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#ifndef dynamic_programming_hpp
#define dynamic_programming_hpp

#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <tuple>
#include "stats.h"

struct TABLE_MEMO{
    std::vector<int> rel_comb;
    int size;
    int cost_join;
    int max_V;
    int max_IDX;
    std::vector<int> best_rel;
    TABLE_MEMO (std::vector<int> rel_comb_ = std::vector<int>(), int a_=0, int a1=0, int a2=0, int a3=0, std::vector<int> best_rel_ = std::vector<int>()): rel_comb(rel_comb_), size(a_), cost_join(a1), max_V(a2), max_IDX(a3), best_rel(best_rel_) {}
};

class dynamic_programming{
public:
    std::vector<int> arr;
    int n;
    int combinatorial[1000] = {0};
    std::vector<TABLE> table_statistic;
    std::vector<std::list<TABLE_MEMO>> vect;
    std::list <TABLE_MEMO> list_;
    dynamic_programming(std::vector<int> arr_, int NRel, const std::vector<TABLE> stat){
        arr = arr_;
        n = NRel;
        table_statistic = stat;
    }
    std::tuple<std::vector<int>, int> plan_generations(std::vector<int> arr, int index, int n, int minimum_total_join);
    int fact(int n);
    int nCr(int n, int r);
    int GetCombID(std::vector<int> comb, int n_sub);
    int calcAndMemoized(std::vector<int> right, int left);
    int construct_memoTable(std::vector<int> arr, int n, int r, int& idx_hash);
    void combinationUtil(std::vector<int> arr, std::vector<int> data,  int start, int end,  int index, int r, int& idx_hash);
    void print_memo_table(int n);
    std::tuple<std::vector<int>, int> getPlan_dynamicProgramming();
    
};

#endif /* dynamic_programming_hpp */
