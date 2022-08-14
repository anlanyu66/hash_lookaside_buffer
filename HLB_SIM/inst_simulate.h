//
// Created by Anlan Yu on 11/23/19.
//

#ifndef HLB_INST_SIMULATE_H
#define HLB_INST_SIMULATE_H
#include <cstddef>
#include <cinttypes>
#include <iostream>
using namespace std;

void hash_lookup_inst(size_t& reg_key, size_t& reg_result) {
    __asm__(
    "mov %1, %%rax\n"   //rax = reg_result
    "mov %2, %%rbx\n"   //rbx = reg_key
    "crc32 %%rax, %%rbx\n"  //simulate lookup_inst(reg_key, reg_result)
    "mov %%rbx, %0\n"       //reg_result = new_reg_result
    :"=r" (reg_result) /* %0: Out */  
    :"r" (reg_result), "r"(reg_key) /* %1, %2: In */ 
    :"rax","rbx"/* Overwrite */
    );
    cout<<reg_result;
}


void hash_insert_inst(size_t &reg_key, size_t &reg_result) {
__asm__(
    "mov %1, %%rax\n"
    "mov %2, %%rbx\n"
    "cmovo %%rax, %%rbx\n"
    "mov %%rbx, %0\n"
    :"=r" (reg_result) /* %0: Out */  
    :"r" (reg_result), "r"(reg_key) /* %1, %2: In */ 
    :"rax","rbx"/* Overwrite */
    );
}


void hash_erase_inst(size_t &reg_key, size_t &reg_result) {
__asm__(
    "mov %1, %%rax\n"
    "mov %2, %%rbx\n"
    "cmovno %%rax, %%rbx\n"
    "mov %%rbx, %0\n"
    :"=r" (reg_result) /* %0: Out */  
    :"r" (reg_result), "r"(reg_key) /* %1, %2: In */ 
    :"rax","rbx"/* Overwrite */
    );
}

void hash_iterator_inst(size_t &reg) {
__asm__(
    "mov %1, %%rax\n"
    "mov %2, %%rbx\n"
    "cmovle %%rax, %%rbx\n"   //for this instruction we only use rax
    "mov %%rbx, %0\n"
    :"=r" (reg) /* %0: Out */  
    :"r" (reg), "r"(reg) /* %1, %2: In */ 
    :"rax","rbx"/* Overwrite */
    );

}
#endif //HLB_INST_SIMULATE_H
