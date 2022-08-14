//
// Created by Anlan Yu on 11/30/19.
//

#ifndef HLB_TEST003_H
#define HLB_TEST003_H
#define KEY_NUM 10000
#define KEY_RANGE 10000
//this test aims to test whether the behaviour is correct
// if we insert and erase kv_pair interleavely
#include "../hlb_api.h"
#include "../Zipfain.h"
#include <set>
#include <random>
using namespace std;

default_random_engine generator;
normal_distribution<double> distribution(0.5,0.167);
//uniform_int_distribution<int> distribution(0, KEY_RANGE);
void test3(){
    set<vector<size_t >> insert_kv;//this contains kv we have inserted by now
    set<vector<size_t >> erase_kv;//this contains kv we have erased by now
    set<vector<size_t >> diff_kv;//this contains the difference between current_kv and erase_kv
    set<vector<size_t >> read_out_kv; // this contains kv we read_out from myhlb by now
    HLB<uint32_t, uint32_t> hlb;
    hlb.clear_hlb();

    for(int i = 0;i<KEY_NUM;i++){
        int rate = rand(); //use this rate to determine whether insert erase or lookup, rules are shown below
        rate = rate % 10;
        if(rate <= 4){
            size_t key = (size_t)distribution(generator)* KEY_RANGE % KEY_RANGE;
            size_t value = (size_t)distribution(generator)* KEY_RANGE % KEY_RANGE;
            hlb.hash_insert(key,value);
            vector<size_t > tmp = {key,value};
            insert_kv.insert(tmp);
//            printf("insert size: %d \n", insert_kv.size());

        }else if(rate == 5 || rate == 6){
            if(insert_kv.size()){
                int id = rand() % insert_kv.size();
                auto it = insert_kv.begin();
                advance(it,id);
                hlb.hash_erase((*it)[0]);
                erase_kv.insert(*it);
//                printf("erase size: %d \n",erase_kv.size());

            }else{
                continue;
            }

        }
        else{
            int d = insert_kv.size();
            if(d){
                int id = rand() % d;
                auto it = insert_kv.begin();
                advance(it,id);
                size_t value = hlb.hash_lookup((*it)[0]);
//                printf("i: %d, lookup key: %d, Value:  %d \n",i, k, value);
            }
            else{
                continue;
            }

        }
    }
    int inst_num = hlb.hlb_iterator_count+hlb.hlb_insert_count+hlb.hlb_erase_count+hlb.hlb_lookup_count;
    cout<<"insert count "<<hlb.hlb_insert_count<<"\n"<<
    "lookup count "<<hlb.hlb_lookup_count<<"\n"<<
    "erase count "<<hlb.hlb_erase_count<<"\n"<<
    "iterator count "<<hlb.hlb_iterator_count<<"\n";
    cout<<"refer memory "<<hlb.mycache->inst_in_mem<<" times\n"<<
    "refer cache "<<hlb.mycache->inst_in_cache<<" times\n"<<
    "total instruction "<<inst_num<<"\n";
}



#endif //HLB_TEST003_H
