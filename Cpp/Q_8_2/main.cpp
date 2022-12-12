#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q8.txt"};
const int mapSize{99};
int map[mapSize][mapSize]{0};

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
    auto start = std::chrono::high_resolution_clock::now();

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

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The highest scenic score possible for any tree: " 
                << maxScenicScore << std::endl;
    return 0;
}