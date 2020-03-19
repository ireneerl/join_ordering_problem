#ifndef stats_h
#define stats_h

#define N_ 4

struct TABLE{
    char name;
    int cost_join_number;
    int joined_variable[N_];
};


//void initialize_basic_data(){
//    table_statistic.push_back({'R', 1000, {100,200,-1,-1}});
//    table_statistic.push_back({'S', 1000, {-1,100,500,-1}});
//    table_statistic.push_back({'T', 1000, {-1,-1,20,50}});
//    table_statistic.push_back({'U', 1000, {50,-1,-1,1000}});
//}

//void initialize_JOB(){
//    table_statistic.push_back({'R', 3, {3,-1,-1,-1,-1}}); //company type
//    table_statistic.push_back({'S', 112, {-1,-1,112,-1,-1}}); //info type
//    table_statistic.push_back({'T', 2609128, {2,2528311,-1,-1,-1}}); //movie company
//    table_statistic.push_back({'U', 1380034, {-1,459925,5,-1,-1}});//movie info idx
//    table_statistic.push_back({'V', 2528311, {-1,2528311,-1,-1,-1}});// title
//}

#endif /* stats_h */
