#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q8.txt"};
const int mapSize{99};
int map[mapSize][mapSize]{0};
bool ifVisible[mapSize][mapSize]{false};

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    char c;
    for(int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            myInputFile.get(c);
            map[i][j] = (int)c;
        }
        myInputFile.get(c);
    }

    for(int i = 0; i < mapSize; i++){
        int lineMax{-1};
        for(int j = 0; j < mapSize; j++){
            if(map[i][j] > lineMax){
                lineMax = map[i][j];
                ifVisible[i][j] = true;
            }
        }
        lineMax = -1;
        for(int j = mapSize - 1; j > -1; j--){
            if(map[i][j] > lineMax){
                lineMax = map[i][j];
                ifVisible[i][j] = true;
            }
        }
    }
    for(int j = 0; j < mapSize; j++){
        int lineMax{-1};
        for(int i = 0; i < mapSize; i++){
            if(map[i][j] > lineMax){
                lineMax = map[i][j];
                ifVisible[i][j] = true;
            }
        }
        lineMax = -1;
        for(int i = mapSize - 1; i > -1; i--){
            if(map[i][j] > lineMax){
                lineMax = map[i][j];
                ifVisible[i][j] = true;
            }
        }
    }

    int nbVisible{0};
    for(int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            nbVisible += ifVisible[i][j];
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The number of trees visible from outside the grid: " 
                << nbVisible << std::endl;
    return 0;
}