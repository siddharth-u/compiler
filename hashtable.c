#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "definitions/hashTableDef.h"

int calculateHash(char* str){
    long long hash_value = 0;
    int n = strlen(str);
    const long long p = 31;
    const long long PRIME = 1000000007;
    long long prime_pow = 1;
    for(int i=0;i<n;i++){
        hash_value = (hash_value + (str[i] * prime_pow) % PRIME) % PRIME;
        prime_pow = (prime_pow * p) % PRIME;
    }
    return hash_value % HASHTABLE_SIZE;
}

void initTable(hash_entry* table){
    for(int i=0;i<HASHTABLE_SIZE;i++){
        table[i].present = false;
    }
}

void insertTable(hash_entry* table, char* lexeme){
    int hash_value = calculateHash(lexeme);
    while(table[hash_value].present == true){
        hash_value = (hash_value + 1) % HASHTABLE_SIZE;
    }
    table[hash_value].present = true;
    strncpy(table[hash_value].lexeme, lexeme, MAX_LEX_LEN);
}

bool searchTable(hash_entry* table, char* lexeme){
    int hash_value = calculateHash(lexeme);
    int probe_no = 0;
    while(table[hash_value].present == true && probe_no < HASHTABLE_SIZE){
        if(strcmp(table[hash_value].lexeme, lexeme) == 0){
            return true;
        }
        hash_value = (hash_value + 1) % HASHTABLE_SIZE;
        probe_no++;
    }
    return false;
}
