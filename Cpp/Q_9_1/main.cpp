#include <fstream>
#include <iostream>
#include <array>
#include <set>
#include <cmath>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q9.txt"};

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    char move;
    int nbSteps;
    std::set<std::array<int, 2>> stepsVisited;
    std::array<int, 2> headLocation{0, 0};
    std::array<int, 2> tailLocation{0, 0};

    while(myInputFile){
        myInputFile >> move;
        myInputFile >> nbSteps;

        for(int step = 0; step < nbSteps; step++){
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

            if(headLocation[0] == tailLocation[0]){
                if(headLocation[1] - tailLocation[1] > 1){
                    tailLocation[1]++;
                }else if(tailLocation[1] - headLocation[1] > 1){
                    tailLocation[1]--;
                }
            }else if(headLocation[1] == tailLocation[1]){
                if(headLocation[0] - tailLocation[0] > 1){
                    tailLocation[0]++;
                }else if(tailLocation[0] - headLocation[0] > 1){
                    tailLocation[0]--;
                }
            }else if(!((std::abs(headLocation[0] - tailLocation[0]) <= 1) && 
                        (std::abs(headLocation[1] - tailLocation[1]) <= 1))){
                if(headLocation[0] > tailLocation[0]){
                    tailLocation[0]++;
                }else{
                    tailLocation[0]--;
                }
                if(headLocation[1] > tailLocation[1]){
                    tailLocation[1]++;
                }else{
                    tailLocation[1]--;
                }
            }

            stepsVisited.insert(tailLocation);
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