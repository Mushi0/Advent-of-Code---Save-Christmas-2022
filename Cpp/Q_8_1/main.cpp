#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::ifstream myInputFile{"..\\..\\Data\\Q8.txt"};
const int mapSize{99};
int map[mapSize][mapSize]{0};
bool ifVisible[mapSize][mapSize]{false};

int main(){
    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }
    
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
    std::cout << "The number of trees visible from outside the grid: " 
                << nbVisible << std::endl;
    
    return 0;
}