#include <fstream>
#include <iostream>
#include <array>
#include <set>
#include <cmath>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q9.txt"};
const int ropeLength{10};

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
            switch(move){
                case 'R':
                    rope[0][0]++;
                    break;
                case 'U':
                    rope[0][1]++;
                    break;
                case 'L':
                    rope[0][0]--;
                    break;
                case 'D':
                    rope[0][1]--;
                    break;
            }

            for(int i = 1; i < ropeLength; i++){
                if(rope[i - 1][0] == rope[i][0]){
                    if(rope[i - 1][1] - rope[i][1] > 1){
                        rope[i][1]++;
                    }else if(rope[i][1] - rope[i - 1][1] > 1){
                        rope[i][1]--;
                    }
                }else if(rope[i - 1][1] == rope[i][1]){
                    if(rope[i - 1][0] - rope[i][0] > 1){
                        rope[i][0]++;
                    }else if(rope[i][0] - rope[i - 1][0] > 1){
                        rope[i][0]--;
                    }
                }else if(!((std::abs(rope[i - 1][0] - rope[i][0]) <= 1) && 
                            (std::abs(rope[i - 1][1] - rope[i][1]) <= 1))){
                    if(rope[i - 1][0] > rope[i][0]){
                        rope[i][0]++;
                    }else{
                        rope[i][0]--;
                    }
                    if(rope[i - 1][1] > rope[i][1]){
                        rope[i][1]++;
                    }else{
                        rope[i][1]--;
                    }
                }
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