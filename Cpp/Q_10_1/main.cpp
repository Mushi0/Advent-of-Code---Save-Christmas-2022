#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q10.txt"};

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    int myRegister{1};
    int nbCycles{0};
    std::string instruction;
    instruction.reserve(4);
    int nbToAdd{0};
    int checkPoint{20};
    int checkPointIncreaseStep{40};
    int signalStrengths{0};
    
    while(myInputFile){
        myInputFile >> instruction;
        if(instruction == "noop"){
            nbCycles++;
            if(nbCycles == checkPoint){
                signalStrengths += (nbCycles*myRegister);
                checkPoint += checkPointIncreaseStep;
            }
        }else{
            myInputFile >> nbToAdd;
            nbCycles++;
            if(nbCycles == checkPoint){
                signalStrengths += (nbCycles*myRegister);
                checkPoint += checkPointIncreaseStep;
            }
            nbCycles++;
            if(nbCycles == checkPoint){
                signalStrengths += (nbCycles*myRegister);
                checkPoint += checkPointIncreaseStep;
            }
            myRegister += nbToAdd;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The sum of the six signal strengths: " 
                << signalStrengths << std::endl;
    return 0;
}