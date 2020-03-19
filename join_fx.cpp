//  Created by Irene Erlyn Wina Rachmawan on 2020/03/02.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#include "join_fx.hpp"

int max_V(int rel_a, int rel_b, std::vector<TABLE> table_statistic){
    int maxV = 1, idx = 0;
    for (int i = 0 ; i < sizeof(table_statistic[0].joined_variable)/sizeof(table_statistic[0].joined_variable[0]); i++){
        if(table_statistic[rel_a].joined_variable[i] != -1 && table_statistic[rel_b].joined_variable[i] != -1){
            maxV = std::max(table_statistic[rel_a].joined_variable[i], table_statistic[rel_b].joined_variable[i]);
            idx = i;
        }
    }
    return maxV; //maximum variable, related coloumn
}

int size_join(std::vector <int> rel_a, int rel_b, int r, int mem_right_product, std::vector<TABLE> table_statistic){
    int join = 0, maxV = 1, upper_product;
    if(mem_right_product == 0 ){ //input:rel_a, rel_b
        if(r == 2){
            auto maxV_ = max_V(rel_a[0], rel_b, table_statistic);
            maxV = maxV_;
            upper_product = (table_statistic[rel_a[0]].cost_join_number * table_statistic[rel_b].cost_join_number);
            join = (upper_product /  maxV);
        }else if (r > 2){
            int common_coloumn = rel_a[0];
            for(int i = 0 ;  i < rel_a.size(); i++){
                auto maxV_ = max_V(rel_a[i], rel_b, table_statistic);
                if(maxV_ > 1 ){
                    common_coloumn = rel_a[i];
                    maxV = maxV_;
                }
            }
            upper_product = (table_statistic[common_coloumn].cost_join_number * table_statistic[rel_b].cost_join_number) ;
            join = (upper_product /  maxV);
        }
//        std::cout << "RESULT -> " << upper_product << "/" << maxV << " = " << join;
        return join;
    }else{ //input:memoization -> rel_a, rel_b
        for(int i = 0 ;  i < rel_a.size(); i++){
            auto maxV_ = max_V(rel_a[i], rel_b, table_statistic);
            if(maxV_ > 1 ){
                maxV = maxV_;
            }
        }join = ((mem_right_product * table_statistic[rel_b].cost_join_number) /  maxV);
        return join;
    }
}

void print_(int rel_a, int rel_b, int maxV){
    std::cout << rel_a << " * " << rel_b << " / " << maxV;
}
