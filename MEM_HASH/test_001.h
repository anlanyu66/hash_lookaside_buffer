//
// Created by Anlan Yu on 12/4/19.
//
#include <iostream>
#include <cassert>
#include <random>
#include <unordered_map>
#include <sstream>
#include <random>
#include <set>

#include "hashmap.h"
#define ITER_NUM 50000
#define KEY_RANGE 1000
#define CACHE_SIZE 1024 * 1024 * 2 / 8
#define MAP_SIZE 1024 * 64
using namespace std;
//this test aims to test whether the behaviour is correct
// if we insert and erase kv_pair interleavely


default_random_engine generator;
//normal_distribution<double> distribution(0.5,0.167);
uniform_int_distribution<int> distribution(0, KEY_RANGE);
void test(){

    hashmap<size_t,size_t> mymap(MAP_SIZE);

    for(int i = 0;i<ITER_NUM;i++){
        int rate = rand(); //use this rate to determine whether insert erase or lookup, rules are shown below
        rate = rate % 10;
        if(rate <= 4){
            size_t key = (size_t)distribution(generator);
            size_t value = (size_t)distribution(generator);
            mymap.set(key,value);
        }else if(rate == 5 || rate == 6){
            size_t key =  (size_t)distribution(generator);
            if(mymap.contain(key))
                mymap.remove(key);
        }
        else{
            int key = (size_t)distribution(generator);
            if(mymap.contain(key))
                mymap.get(key);

        }
    }
    cout<<"refer memory "<<mymap.mem_lookup_count<<" times\n"<<
    "refer cache "<<mymap.cache_lookup_count<<" times\n";

}
