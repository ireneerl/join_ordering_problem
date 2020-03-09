//  Created by Irene Erlyn Wina Rachmawan on 2020/03/09.
//  Copyright © 2020 Irene - lynrc. All rights reserved.

#include "../incl/simulated_annealing.hpp"
#include "../incl/join_fx.hpp"

int simulated_annealing::join_cost_function(std::vector<int> trialSolution, int n){
    int size_join_res = 100000000, join_cost_res = 100000000, maxV=1, max_IDX = 0;
    std::vector<int> right; int left=0, total_size = 0, total_join = 0;
    int global_maxV;
    
    for (int r = 1 ; r <= n ; r++){
        left = trialSolution[r-1];
        if(r == 1){
            size_join_res = table_statistic[trialSolution[r-1]].cost_join_number;
            size_join_res = table_statistic[trialSolution[r-1]].cost_join_number;
            join_cost_res = 0;
        }else if(r == 2){
            right.push_back((trialSolution[r-2] -1 ));
            size_join_res = size_join(right,left - 1, r, 0, table_statistic);
            join_cost_res = 0;
            global_maxV = maxV;
            
        }else{
            right.push_back((trialSolution[r-2] -1));
            join_cost_res = total_size;
            size_join_res = size_join(right,left - 1, r, 0, table_statistic);
        }
        total_size = size_join_res;
        total_join += join_cost_res;
        // std::cout << "total size "<< total_size << " total join "<< total_join << std::endl;
        
    }
    return total_join;
}

//simulated annealing related func

std::vector<int> simulated_annealing::new_solution (std::vector<int> arr, int NRel){
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(arr), std::end(arr), rng);
    return arr;
}

double simulated_annealing::initiate_Temperature(std::vector<int> arr, int Nrel){
    double sumRel = 0;
    for(int i = 0 ; i < Nrel ; i++){
        std::vector<int> tmp = new_solution(arr,Nrel);
        int join_size = join_cost_function(tmp, Nrel);
        if(join_size > sumRel){
            sumRel = join_size;
        }
    }
    return 2*sumRel;
    // return 200;
}

std::tuple<std::vector<int>, int> simulated_annealing::annealing_process(std::vector<int> arr, double temp, int Nrel){
    double decT = 0.99;
    double T = temp;
    int minimum_join_cost, new_join_size;
    std::vector<int> new_rel_path, best_path;
    int smallest_join_cost = join_cost_function(arr, Nrel);
    
    for(int i = 0; i < 5 ; i++){
        minimum_join_cost = join_cost_function(arr, Nrel);
        new_rel_path = new_solution(arr, Nrel);
        std::cout << "state i -> ";
        for(int x = 0 ; x < Nrel; x++ ){
            std::cout <<  arr[x] << " ";
        }std::cout << " ; ";
        std::cout << "state i + 1 -> ";
        for(int x = 0 ; x < Nrel; x++ ){
            std::cout <<  new_rel_path[x] << " ";
        }
        new_join_size = join_cost_function(new_rel_path, Nrel);
        
        std::cout << "energy i -> " << minimum_join_cost << "; new energy -> " << new_join_size;
        if(new_join_size < minimum_join_cost){
            minimum_join_cost = new_join_size;
            arr = new_rel_path;
            if(minimum_join_cost < smallest_join_cost){
                smallest_join_cost = minimum_join_cost;
                best_path = arr;
            }
        }else{
            double rndNumber = ((double) rand() / (RAND_MAX));
            float temp_cooling = exp(-1 * (new_join_size - smallest_join_cost) / T);
            // std::cout << "random number and its exponential border : " << rndNumber << " & " << temp_cooling;
            if(rndNumber < temp_cooling){
                std::cout << " ** "; //it is not smaller join cost but exploring the area for possible global minima
                arr = new_rel_path;
            }//else ; maintain arr;
        }
        T = decT * T;
        std::cout << std::endl;
    }
    return{arr, smallest_join_cost};
}

std::tuple<std::vector<int>, int> simulated_annealing::getPlan_simulatedAnnealing(){
    std::vector <int> SA;
    int minimum_total_join;
    srand (time(NULL));
    double initiate_T = initiate_Temperature(arr, n);
    std::tie(SA, minimum_total_join) = annealing_process(arr, initiate_T, n);
    return {SA, minimum_total_join};
}
