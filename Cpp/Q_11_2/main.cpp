#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include <bits/stdc++.h>
#include <chrono>

// std::ifstream myInputFile{"..\\..\\Data\\Q11.txt"};
const int nbRounds = 10000;
const int nbMonkeys = 8;

struct monkey{
    std::vector<int> originalItems;
    char operation;
    int operand;
    int divisor;
    int resultTrue;
    int resultFalse;
    int nbInspects{0};
    std::vector<std::array<int, nbMonkeys>> items;
};

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    monkey monkeys[nbMonkeys];
    std::vector<int> itemsVec = {54, 82, 90, 88, 86, 54};
    monkey newMonkey = monkey{itemsVec, '*', 7, 11, 2, 6};
    monkeys[0] = newMonkey;
    itemsVec = {91, 65};
    newMonkey = monkey{itemsVec, '*', 13, 5, 7, 4};
    monkeys[1] = newMonkey;
    itemsVec = {62, 54, 57, 92, 83, 63, 63};
    newMonkey = monkey{itemsVec, '+', 1, 7, 1, 7};
    monkeys[2] = newMonkey;
    itemsVec = {67, 72, 68};
    newMonkey = monkey{itemsVec, '^', 2, 2, 0, 6};
    monkeys[3] = newMonkey;
    itemsVec = {68, 89, 90, 86, 84, 57, 72, 84};
    newMonkey = monkey{itemsVec, '+', 7, 17, 3, 5};
    monkeys[4] = newMonkey;
    itemsVec = {79, 83, 64, 58};
    newMonkey = monkey{itemsVec, '+', 6, 13, 3, 0};
    monkeys[5] = newMonkey;
    itemsVec = {96, 72, 89, 70, 88};
    newMonkey = monkey{itemsVec, '+', 4, 3, 1, 2};
    monkeys[6] = newMonkey;
    itemsVec = {79};
    newMonkey = monkey{itemsVec, '+', 8, 19, 4, 5};
    monkeys[7] = newMonkey;

    for(int monkeynb = 0; monkeynb < nbMonkeys; monkeynb++){
        std::vector<std::array<int, nbMonkeys>> itemsRemainderVec;
        for(int item = 0; item < monkeys[monkeynb].originalItems.size(); item++){
            std::array<int, nbMonkeys> itemRemainder;
            for(int i = 0; i < nbMonkeys; i++){
                itemRemainder[i] = monkeys[monkeynb].originalItems[item] % 
                                    monkeys[i].divisor;
            }
            itemsRemainderVec.push_back(itemRemainder);
        }
        monkeys[monkeynb].items = itemsRemainderVec;
    }

    for(int roundnb = 0; roundnb < nbRounds; roundnb++){
        for(int monkeynb = 0; monkeynb < nbMonkeys; monkeynb++){
            for(int item = 0; item < monkeys[monkeynb].items.size(); item++){
                std::array<int, nbMonkeys> itemRemainder;
                for(int i = 0; i < nbMonkeys; i++){
                    switch (monkeys[monkeynb].operation){
                    case '+':
                        itemRemainder[i] = ((monkeys[monkeynb].items[item][i] + 
                                            monkeys[monkeynb].operand) % 
                                            monkeys[i].divisor);
                        break;
                    case '*':
                        itemRemainder[i] = ((monkeys[monkeynb].items[item][i] * 
                                            monkeys[monkeynb].operand) % 
                                            monkeys[i].divisor);
                        break;
                    case '^':
                        itemRemainder[i] = ((monkeys[monkeynb].items[item][i] * 
                                            monkeys[monkeynb].items[item][i]) % 
                                            monkeys[i].divisor);
                        break;
                    default:
                        itemRemainder[i] = 0;
                        break;
                    }
                }

                monkeys[monkeynb].nbInspects++;

                if(itemRemainder[monkeynb] == 0){
                    monkeys[monkeys[monkeynb].resultTrue].items.push_back(itemRemainder);
                }else{
                    monkeys[monkeys[monkeynb].resultFalse].items.push_back(itemRemainder);
                }
            }
            monkeys[monkeynb].items = {};
        }
    }

    int inspects[nbMonkeys];
    for(int i = 0; i < nbMonkeys; i++){
        inspects[i] = monkeys[i].nbInspects;
    }
    std::sort(inspects, inspects + nbMonkeys, std::greater<int>());

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The level of monkey business after " << nbRounds << " rounds: " 
                << (long long)inspects[0]*inspects[1] << std::endl;
    return 0;
}