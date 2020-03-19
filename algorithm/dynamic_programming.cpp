//  Created by Irene Erlyn Wina Rachmawan on 2020/03/03.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#include "../incl/dynamic_programming.hpp"
#include "../incl/join_fx.hpp"

std::tuple<std::vector<int>, int> dynamic_programming::plan_generations(std::vector<int> arr, int index, int n, int minimum_total_join){
    std::vector <int> DP_solution;
    return {DP_solution, 0};
}

int dynamic_programming::fact(int n) { //also DP
    if (n >= 0) {
        combinatorial[0] = 1;
        for (int i = 1; i <= n; ++i) {
            combinatorial[i] = i * combinatorial[i - 1];
        }
    }
    return combinatorial[n];
}

int dynamic_programming::nCr(int n, int r){
    return fact(n) / (fact(r) * fact(n-r));
}

int dynamic_programming::GetCombID(std::vector<int> comb, int n_sub){
    int k = comb.size(), id = nCr(n_sub, k);
    for (int i = 0; i < k; i++){
        int new_n = n_sub - comb[i];
        int new_k = k-i;
        if(new_k <= new_n){
            id -= nCr(new_n, new_k);
        }
    }
    return (int)id;
}

int dynamic_programming::calcAndMemoized(std::vector<int> right, int left) {
    for(auto& element : right)
        element += 1;
//    for (int i = 0 ; i < right.size() ; i++){
//        std::cout << " "<< right[i] ;
//    }std::cout << " //";
    int mem_idx = (GetCombID(right,4)-1);
//    std::cout << "PRINT MEM ID "<< mem_idx << " ;; ";
    int right_size = right.size();
    int mem_cost, mem_maxV;
    if(right_size > 1){
        std::list<TABLE_MEMO>::iterator x = std::next(vect[(right.size()-1)].begin(), mem_idx); //prev hash bucket, with found memoized id
        mem_cost = x->size;
        mem_maxV = x->max_V;
    }
    return mem_cost;
}

int dynamic_programming::construct_memoTable(std::vector<int> arr, int n, int r, int& idx_hash){
    
    std::vector<int> right;
    int left;
    //first memoization// std::cout << r << ".MAJOR HASH just passing "<<  n << " ; " << idx_hash << std::endl;
    if(r == 1){
        std::vector<int> joined_rel(r) ;
        joined_rel.assign(&arr[0], &arr[r]);
        TABLE_MEMO head(joined_rel, table_statistic[idx_hash-1].cost_join_number, 0, 0, 0, joined_rel);
        list_.push_back(head);
    }else {
        int size_join_res = 100000000, join_cost_res = 100000000, maxV=1, max_IDX = 0;
        std::vector<int> joined_rel(right.size()) ;
        std::vector<int> origin(r) ;
        origin.assign(&arr[0], &arr[r]);
        for (int i = 0 ; i < r ; i++){
            right = arr;
            right.erase (right.begin()+i);
            for(auto& element : right)
                element -= 1;
            left = arr[i];
            int temp_cost = 100000000;
            if(r == 2){
                temp_cost = size_join(right,left - 1, r, 0, table_statistic);
                if(temp_cost < size_join_res){
                    size_join_res = temp_cost;
                    joined_rel.assign({right[0]+1,left});
                    join_cost_res = 0;
                }
            }else{
                int coloumn_idx = 0;
                int cost_mem = calcAndMemoized(right, left); //memoization size
                if(cost_mem < join_cost_res){
                    join_cost_res = cost_mem;
                    joined_rel.assign(right.begin(),right.begin()+(r-1));
                    while(coloumn_idx < right.size()){
                        size_join_res = size_join(right,left - 1, r, cost_mem, table_statistic);
                        coloumn_idx++;
                    }
                }
            }
        }
        for(auto& element : joined_rel)
            element += 1;
        TABLE_MEMO head(origin,size_join_res, join_cost_res, maxV, max_IDX, joined_rel); //0-> calculate function
        list_.push_back(head);
    }
    return ++idx_hash;
}

void dynamic_programming::combinationUtil(std::vector<int> arr, std::vector<int> data,  int start, int end,  int index, int r, int& idx_hash) {
    if (index == r)  {
//        for (int j = 0; j < r; j++)  {
//            std::cout << data[j] << " ";
//        }std::cout << ";" << std::endl;
        if(end>=r || r == end+1){
            idx_hash = construct_memoTable(data,end,r, idx_hash); // if the last combination doesnt need this, separate if without this line
        }
        return;
    }
    for (int i = start; i <= end &&  end - i + 1 >= r - index; i++)  {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1,  end, index+1, r, idx_hash);
    }
}

void dynamic_programming::print_memo_table(int N_rel){
    for(int i=0;i<N_rel;i++){
        for(auto x: vect[i]) {
            for (int i = 0; i < x.rel_comb.size(); i++) {
                std::cout << x.rel_comb.at(i) << ';';
            }
            std::cout << " " << x.size << " " << x.cost_join << " ";
            for (int i = 0; i < x.best_rel.size(); i++) {
                std::cout << x.best_rel.at(i) << ';';
            }std::cout << std::endl;
        }std::cout << std::endl;
    }
}

std::tuple<std::vector<int>, int> dynamic_programming::getPlan_dynamicProgramming(){
    std::vector <int> DP_solution;
    for (int r = 1; r <= n ; r++){
        std::vector<int> data (r);
        int idx_hash = 1;
        combinationUtil(arr, data, 0, n-1, 0, r, idx_hash);
        vect.push_back(list_);
//        print_memo_table(r);
        list_.clear();
    }
    
    //traceback
    int memid=0,total=0;
    for(int i = n-1 ; i > 0 ; i--){
        std::list<TABLE_MEMO>::iterator x = std::next(vect[i].begin(), memid);
//        memid = (GetCombID(x->best_rel,n)-1);
//        std::cout << "at level "<<i<<" : "<< memid << ";";
        total += x->cost_join;
    }

    return {DP_solution, total};
}
