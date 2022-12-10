#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q10.txt"};
const int mapWide{40};
const int mapHigh{6};

void drawSignal(int map[], int nbCycles, int myRegister){
    if(std::abs(nbCycles%mapWide - myRegister) <= 1){
        if(map[nbCycles] == 1){
            if(map[nbCycles + 1] == 1){
                map[nbCycles + 2] = 1;
            }else{
                map[nbCycles + 1] = 1;
            }
        }else{
            map[nbCycles] = 1;
        }
    }
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    int myRegister{1};
    int nbCycles{0};
    std::string instruction;
    instruction.reserve(4);
    int nbToAdd{0};
    int map[mapWide*mapHigh]{0};
    
    while(myInputFile){
        myInputFile >> instruction;
        if(instruction == "noop"){
            drawSignal(map, nbCycles, myRegister);
            nbCycles++;
        }else{
            myInputFile >> nbToAdd;
            drawSignal(map, nbCycles, myRegister);
            nbCycles++;
            drawSignal(map, nbCycles, myRegister);
            nbCycles++;
            myRegister += nbToAdd;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    int thisSignal{0};
    for(int i = 0; i < mapHigh; i++){
        for(int j = 0; j < mapWide; j++){
            thisSignal = map[i*mapWide + j];
            if(thisSignal){
                std::cout << "# ";
            }else{
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}