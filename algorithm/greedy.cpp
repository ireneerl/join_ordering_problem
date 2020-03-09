//  Created by Irene Erlyn Wina Rachmawan on 2020/03/02.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#include "../incl/greedy.hpp"
#include "../incl/join_fx.hpp"


std::vector<int> greedy::findRestoftheElement(std::vector<int> relations, std::vector<int> greddy_curr_solution, int n){
    std::vector<int> rest;
    for(int x=0; x<n-1; x++){
        int j ;
        for(j = 0 ; j < greddy_curr_solution.size() ; j++){
            if(relations[x] == greddy_curr_solution[j])
                break;
        }
        if(j == greddy_curr_solution.size()){
            rest.push_back (relations[x]);
        }
    }
    return rest;
}

std::tuple<int, int> greedy::greedy_move(std::vector<int> &greedy_solution, std::vector<int> rest, int n, int r, int size_join_prev, int join_cost_prev){
    std::vector<int> right = greedy_solution;
    int temp_total_size, temp_total_join = size_join_prev, size_join_res = size_join_prev, join_cost_res = 10000000, left;
    
    for(int x = 0; x < rest.size();x++){
        left = rest[x];
        temp_total_size = size_join(right,left - 1, r, 0, table_statistic);
        temp_total_join += join_cost_prev;
        
        if (temp_total_join <= join_cost_res){
            size_join_res = temp_total_size;
            join_cost_res = temp_total_join;
            if(greedy_solution.size() == r){
                greedy_solution.pop_back();
            }greedy_solution.push_back(rest[x]);
        }
    }
    
    return {size_join_res, join_cost_res};
}

std::tuple<int, int> greedy::initial_plan_generations(std::vector<int> arr, std::vector<int> data,  int start, int end,  int index, int r, int *total_size, int *total_join, std::vector<int> &greedy_solution) {
    if (index == r)  {
//        for (int j = 0; j < r; j++)  {
//            std::cout << data[j] << " ";
//        }std::cout << std::endl;
        int i = r-1; //r starts from the sequence number, translates the r to array indices
        int size_join_res, join_cost_res;
        std::vector<int> right; int left=0;
        right = data;
        left = right[i];
        right.erase (right.begin()+(i));
        
        if(r == 1){
            size_join_res = table_statistic[data[i]].cost_join_number;
            join_cost_res = 0;
            return{size_join_res, join_cost_res};
        }else if(r == 2){
            size_join_res = size_join(right,left - 1, r, 0, table_statistic);
            join_cost_res = 0;
            if (size_join_res <= *total_size){
                *total_size = size_join_res;
                *total_join = join_cost_res;
                if(!greedy_solution.empty()){
                    greedy_solution.pop_back();
                    greedy_solution.pop_back();
                }
                greedy_solution.push_back(right[i-1]);
                greedy_solution.push_back(left);
            }
            return {size_join_res, join_cost_res};
        }
    }
    for (int i = start; i <= end &&  end - i + 1 >= r - index; i++)  {
        data[index] = arr[i];
        std::tie(*total_size, *total_join) = initial_plan_generations(arr, data, i+1,  end, index+1, r, total_size, total_join, greedy_solution);
    }
    return {*total_size, *total_join};
}

std::tuple<std::vector<int>, int> greedy::getPlan_greedy(){
    std::cout << "ENTERING GREEDY ..." << std::endl;
    std::vector<int> greedy_solution;
    int size = 1000000, join = 1000000, tmp_total_size_, tmp_total_join_;
    for (int r = 1; r <= n ; r++){
        std::vector<int> data (r);
        if(r <= 2){
            std::tie(tmp_total_size_, tmp_total_join_) = initial_plan_generations(arr, data, 0, n-1, 0, r, &size, &join, greedy_solution);
            size = tmp_total_size_;
            join = tmp_total_join_;
        }
        else{
            std::vector<int> rest = greedy::findRestoftheElement(arr, greedy_solution, n);
            std::tie(tmp_total_size_, tmp_total_join_) = greedy_move(greedy_solution, rest, n, r, size, join);
            size = tmp_total_size_;
            join = tmp_total_join_;
        }
        for(int i = 0 ; i < greedy_solution.size(); i++){
            std::cout << greedy_solution[i] << " ";
        } std::cout << std::endl;
    }return {greedy_solution, join};
}

