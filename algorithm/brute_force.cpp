//  Created by Irene Erlyn Wina Rachmawan on 2020/03/02.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#include "../incl/brute_force.h"
#include "../incl/join_fx.hpp"

std::tuple<std::vector<int>, int> brute_force::plan_generations(std::vector<int> arr, int index, int n, int minimum_total_join) {
    std::vector<int> path;
    if (index == n){
        int size_join_res = 100000000, join_cost_res = 100000000, maxV=1;
        std::vector<int> right; int left=0, total_size = 0, total_join = 0;
        int global_maxV;
        //the plan that is being evaluated
        for (int j = 0; j < n; j++)  {
            std::cout << arr[j] << " ";
        }
        for (int r = 1 ; r <= n ; r++){
            left = arr[r-1];
            if(r == 1){
                size_join_res = table_statistic[arr[r-1]].cost_join_number;
                join_cost_res = 0;
            }else if(r == 2){
                right.push_back((arr[r-2] -1 ));
                join_cost_res = 0;
                size_join_res = size_join(right,left - 1, r, 0, table_statistic);
                global_maxV = maxV;
            }else{
                right.push_back((arr[r-2] -1));
                join_cost_res = total_size;
                size_join_res = size_join(right,left - 1,r, 0, table_statistic);
            }
            std::cout << " join -> " << size_join_res;
            
            total_size = size_join_res;
            total_join += join_cost_res;
        }
//        std::cout << " here is the current smaller result -> " << minimum_total_join;
        if (total_join <= minimum_total_join){
            minimum_total_join = total_join;
            std::cout << " ;  here is the smaller result -> " << total_join << std::endl;
            path = arr;
        }
        std::cout << std::endl;;
        return {path, minimum_total_join};
    }
    
    for (unsigned int i=index; i<n; i++){
        std::swap(arr[i], arr[index]);
        std::vector<int> path_;
        std::tie(path_, minimum_total_join) = plan_generations(arr, index+1, n, minimum_total_join);
        if(path_.size() > 0 )
            path = path_;
        std::swap(arr[i], arr[index]);
    }
    return {path, minimum_total_join};
}

std::tuple<std::vector<int>, int> brute_force::getPlan_bruteForce(){
    std::cout << "ENTERING BRUTE FORCE ..." << std::endl;
    std::vector<int> path;
    int minimum_total_join;
    std::tie(path, minimum_total_join) = plan_generations(arr, 0, n, 1000000000);
    return {path, minimum_total_join};
}
