#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::ifstream myInputFile{"..\\..\\Data\\Q8.txt"};
const int mapSize{99};
int map[mapSize][mapSize]{0};
bool ifVisible[mapSize][mapSize]{false};

int calScenicScore(int ii, int jj){
    if((ii == 0) || (ii == mapSize - 1) || (jj == 0) || (jj == mapSize - 1)){
        return 0;
    }
    int scenicScore{1};
    int thisHeight{map[ii][jj]};
    int i{ii - 1};
    int count{1};
    while(map[i][jj] < thisHeight){
        count++;
        i--;
        if(i == -1){
            count--;
            break;
        }
    }
    scenicScore *= count;
    i = ii + 1;
    count = 1;
    while(map[i][jj] < thisHeight){
        count++;
        i++;
        if(i == mapSize){
            count--;
            break;
        }
    }
    scenicScore *= count;
    int j{jj - 1};
    count = 1;
    while(map[ii][j] < thisHeight){
        count++;
        j--;
        if(j == -1){
            count--;
            break;
        }
    }
    scenicScore *= count;
    j = jj + 1;
    count = 1;
    while(map[ii][j] < thisHeight){
        count++;
        j++;
        if(j == mapSize){
            count--;
            break;
        }
    }
    scenicScore *= count;
    return scenicScore;
}

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

    int maxScenicScore{0};
    for(int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            int scenicScore = calScenicScore(i, j);
            if(scenicScore > maxScenicScore){
                maxScenicScore = scenicScore;
            }
        }
    }
    std::cout << "The highest scenic score possible for any tree: " 
                << maxScenicScore << std::endl;
    
    return 0;
}