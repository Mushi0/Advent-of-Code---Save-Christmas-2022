#include <fstream>
#include <iostream>
#include <array>
#include <set>
#include <cmath>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q9.txt"};
const int ropeLength{10};

void moveHead(std::array<int, 2>& headLocation, char move){
    switch(move){
        case 'R':
            headLocation[0]++;
            break;
        case 'U':
            headLocation[1]++;
            break;
        case 'L':
            headLocation[0]--;
            break;
        case 'D':
            headLocation[1]--;
            break;
    }
}

void followMove(std::array<int, 2>& thisLocation, std::array<int, 2>& previousLocation){
    if(previousLocation[0] == thisLocation[0]){
        if(previousLocation[1] - thisLocation[1] > 1){
            thisLocation[1]++;
        }else if(thisLocation[1] - previousLocation[1] > 1){
            thisLocation[1]--;
        }
    }else if(previousLocation[1] == thisLocation[1]){
        if(previousLocation[0] - thisLocation[0] > 1){
            thisLocation[0]++;
        }else if(thisLocation[0] - previousLocation[0] > 1){
            thisLocation[0]--;
        }
    }else if(!((std::abs(previousLocation[0] - thisLocation[0]) <= 1) && 
                (std::abs(previousLocation[1] - thisLocation[1]) <= 1))){
        if(previousLocation[0] > thisLocation[0]){
            thisLocation[0]++;
        }else{
            thisLocation[0]--;
        }
        if(previousLocation[1] > thisLocation[1]){
            thisLocation[1]++;
        }else{
            thisLocation[1]--;
        }
    }
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    char move;
    int nbSteps;
    std::set<std::array<int, 2>> stepsVisited;
    std::array<std::array<int, 2>, ropeLength> rope;
    for(int i = 0; i < ropeLength; i++){
        rope[i] = {0, 0};
    }

    while(myInputFile){
        myInputFile >> move;
        myInputFile >> nbSteps;

        for(int step = 0; step < nbSteps; step++){
            moveHead(rope[0], move);
            for(int i = 1; i < ropeLength; i++){
                followMove(rope[i], rope[i - 1]);
            }
            stepsVisited.insert(rope[ropeLength - 1]);
        }
        myInputFile.ignore(1);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The number of positions the tail visit at least once: " 
                << stepsVisited.size() << std::endl;
    return 0;
}