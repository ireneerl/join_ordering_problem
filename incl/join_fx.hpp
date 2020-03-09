//
//  join_fx.hpp
//  join_ordering
//
//  Created by Irene Erlyn Wina Rachmawan on 2020/03/02.
//  Copyright © 2020 Irene - lynrc. All rights reserved.
//

#ifndef join_fx_hpp
#define join_fx_hpp

#include "join_fx.hpp"
#include <iostream>
#include <vector>
#include "stats.h"

int max_V(int rel_a, int rel_b, std::vector<TABLE> table_statistic);
int size_join(std::vector <int> rel_a, int rel_b, int r, int right_product, std::vector<TABLE> table_statistic);
void print_(int rel_a, int rel_b, int maxV);


#endif /* join_fx_hpp */
