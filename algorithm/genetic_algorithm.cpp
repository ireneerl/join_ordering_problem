//
//  genetic_algorithm.cpp
//  join_ordering
//
//  Created by Irene Erlyn Wina Rachmawan on 2020/03/09.
//  Copyright © 2020 Irene - lynrc. All rights reserved.
//

#include "../incl/genetic_algorithm.hpp"
#include "../incl/join_fx.hpp"


void genetic_algorithm::printPopulation(std::vector<INDVI> comm){
    std::cout << std::endl;
    for(int indv = 0; indv < comm.size() ; indv++){
        std::cout << "#" << indv;
        for(int gen = 0 ; gen < comm[indv].gens.size() ; gen++){
            std::cout << " " << comm[indv].gens[gen];
        }
        std::cout << " ; cost = " << comm[indv].cost << " ; fitness value = " << comm[indv].fitness_val << std::endl;
    }
}

void genetic_algorithm::generate_population(std::vector<int> arr, int NRel, int NIndiv){
    for(int indv = 0; indv < NIndiv ; indv++){
        std::vector<int> temp;
        for (int i = 0; i < NRel; i++){
            int j = i + rand() % (NRel - i);
            std::swap(arr[i], arr[j]);
            temp.push_back(arr[i]);
        }
        population.push_back({temp, 0, -1, -1});
    }
}

void genetic_algorithm::fitness_function(int N_indv, int n){
    for(int x_indv = 0 ; x_indv < N_indv ; x_indv++){
        int size_join_res = 100000000, join_cost_res = 100000000, maxV=1, max_IDX = 0;
        std::vector<int> right; int left=0, temp_total_size = 0, temp_total_join = 0;
        for (int r = 1 ; r <= n ; r++){
            left = population[x_indv].gens[r-1];
            if(r == 1){
                size_join_res = table_statistic[population[x_indv].gens[r-1]].cost_join_number;
                join_cost_res = 0;
            }else if(r == 2){
                right.push_back(population[x_indv].gens[r-2] - 1);
                size_join_res = size_join(right,left - 1, r, 0, table_statistic);
                join_cost_res = 0;
            }else{
                right.push_back(population[x_indv].gens[r-2] - 1);
                join_cost_res = size_join_res;
                size_join_res = size_join(right,left - 1, r, 0, table_statistic);
            }
            
            temp_total_size = size_join_res;
            temp_total_join += join_cost_res;
        }
        population[x_indv].cost = temp_total_join;
        population[x_indv].size = temp_total_size;
        population[x_indv].fitness_val = 1.0/temp_total_join;
    }
//    std::cout << std::endl;
    // return {total_size, total_join};
}

void genetic_algorithm::select_parents(int NIndiv, int NRel){
    std::vector <std::vector <int> > new_parents;
    double totalFitness = 0;int i;
    for(i=0;i<NIndiv;i++){
        totalFitness += population[i].fitness_val;
    }
    for(i=0;i<NIndiv;i++){
        population[i].probability = (population[i].fitness_val)/totalFitness;
    }
    
    for (int new_P = 0; new_P < NIndiv; new_P++) {
        double rndNumber = rand() / (double) RAND_MAX, offset = 0.0;
        INDVI parent_choosen;
        for (i = 0; i < NIndiv; i++) {
            offset += population[i].probability;
            if (rndNumber < offset) {
                parent_choosen = population[i];
                break;
            }
        }
        parents.push_back(parent_choosen);
    }
}

void genetic_algorithm::crossOver(double prob, int n){
    children = parents;
    for(int pair_idx = 0 ; pair_idx < n/2 ; pair_idx++){
        srand (time(NULL));
        double rndNumber = ((double) rand() / (RAND_MAX)) + 1;
        int id_parent1 = pair_idx * 2, id_parent2 = pair_idx * 2 + 1;
        if(rndNumber < prob){
            int left = rand() % 5 + 1;
            int right = rand() % 10 + left;
            for(int COx = left ; COx < right ; COx++){
                std::vector<int>::iterator it_parent1 = std::find(parents[id_parent1].gens.begin(), parents[id_parent1].gens.end(), parents[id_parent2].gens[COx]);
                int idx_origin_p1 = std::distance(parents[id_parent1].gens.begin(), it_parent1);
                std::vector<int>::iterator it_parent2 = std::find(parents[id_parent2].gens.begin(), parents[id_parent2].gens.end(), parents[id_parent1].gens[COx]);
                int idx_origin_p2 = std::distance(parents[id_parent2].gens.begin(), it_parent2);
                
                //crossing over
                children[id_parent1].gens[idx_origin_p1] = children[id_parent1].gens[COx];
                children[id_parent2].gens[idx_origin_p2] = children[id_parent2].gens[COx];
                int tmp = parents[id_parent1].gens[COx];
                children[id_parent1].gens[COx] = children[id_parent2].gens[COx];
                children[id_parent2].gens[COx] = tmp;
            }
        }
    }
}

void genetic_algorithm::mutation(double prob, int nrel){
    for(int idv = 0 ; idv < nrel ; idv++){
        srand (time(NULL));
        double rndNumber = ((double) rand() / (RAND_MAX)) + 1;
        if(rndNumber < prob){
            int idx_mutated = rand() % nrel + 1;
            int tmp = children[idv].gens[idx_mutated];
            if(children[idv].gens[idx_mutated] < nrel && children[idv].gens[idx_mutated] > 1)
            {
                int mutation = children[idv].gens[idx_mutated]+1;
                std::vector<int>::iterator t_idv = std::find(children[idv].gens.begin(), children[idv].gens.end(), mutation);
                int idx_origin_ = std::distance(children[idv].gens.begin(), t_idv);
                children[idv].gens[idx_origin_] = tmp;
                children[idv].gens[idx_mutated] = mutation;
            }
        }
    }
}

std::tuple<std::vector<int>, int> genetic_algorithm::getPlan_geneticAlgorithm(){
    //GA parameters
    std::vector <int> GA_indiv;
    int NIndiv = 10;
    srand ( time(NULL) );
    
    generate_population(arr, n, NIndiv);
    for(int i = 0 ; i < Nevolution ; i ++ ){
        fitness_function(NIndiv, n);
//        printPopulation(population);
        select_parents(NIndiv, n);
//        printPopulation(parents);
        crossOver(0.6, NIndiv);
//        printPopulation(children);
        mutation(0.6, n);
//        printPopulation(children);
        population.clear();
        parents.clear();
        population = children;
    }
    
    std::sort(population.begin(), population.end(), [&](const INDVI a, const INDVI b){
        return a.fitness_val > b.fitness_val;
    });
//    printPopulation(population);
    return {population[0].gens,population[0].cost};
}
