//
//  join_func.hpp
//  join_ordering
//
//  Created by Irene Erlyn Wina Rachmawan on 2020/02/28.
//  Copyright © 2020 Irene - lynrc. All rights reserved.
//

#ifndef join_func_hpp
#define join_func_hpp

#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include "stats.h"


class join_func
{
public:
    std::vector <int> rel_a;
    int rel_b, r, right_product;
    
    join_func(std::vector <int> a, int b, int c, int d){
        rel_a = a;
        rel_b = b;
        r = c;
        right_product = d;
    }
    
    static const std::vector<TABLE> table_statistic;
    int max_V(int rel_a, int rel_b);
    int size_join();
};


#endif /* join_func_hpp */
