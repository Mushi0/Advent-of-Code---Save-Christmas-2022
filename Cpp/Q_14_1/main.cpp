#include <fstream>
#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q14.txt"};
int source{500};

std::vector<std::string> strsplit(std::string strToSplit, char delimeter){
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while(std::getline(ss, item, delimeter)){
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    std::string onePath;
    int nbColumn{529};
    int nbRow{167};
    int map[nbRow][nbColumn]{0};

    while(std::getline(myInputFile, onePath)){
        std::vector<std::string> segments = strsplit(onePath, '-');
        for(int segmentnb = 0; segmentnb < segments.size() - 1; segmentnb++){
            std::vector<std::string> startLocation = strsplit(segments[segmentnb], ',');
            std::vector<std::string> endLocation = strsplit(segments[segmentnb + 1], ',');
            int startLocationInt[2] = {std::stoi(startLocation[0]), std::stoi(startLocation[1])};
            int endLocationInt[2] = {std::stoi(endLocation[0]), std::stoi(endLocation[1])};

            if(startLocationInt[0] == endLocationInt[0]){
                int smallerStep{std::min(startLocationInt[1], endLocationInt[1])};
                int largerStep{std::max(startLocationInt[1], endLocationInt[1])};
                for(int step = smallerStep; step <= largerStep; step++){
                    map[step][startLocationInt[0]] = 1;
                }
            }else{
                int smallerStep{std::min(startLocationInt[0], endLocationInt[0])};
                int largerStep{std::max(startLocationInt[0], endLocationInt[0])};
                for(int step = smallerStep; step <= largerStep; step++){
                    map[startLocationInt[1]][step] = 1;
                }
            }
        }
    }

    int nbRest{0};
    int sandLocation[2]{source, 0};
    while(true){
        if(sandLocation[0] >= nbColumn - 1 || sandLocation[1] >= nbRow - 1){
            break;
        }
        if(map[sandLocation[1] + 1][sandLocation[0]] == 0){
            sandLocation[1] += 1;
            continue;
        }else if(map[sandLocation[1] + 1][sandLocation[0] - 1] == 0){
            sandLocation[0] -= 1;
            sandLocation[1] += 1;
            continue;
        }else if(map[sandLocation[1] + 1][sandLocation[0] + 1] == 0){
            sandLocation[0] += 1;
            sandLocation[1] += 1;
            continue;
        }
        map[sandLocation[1]][sandLocation[0]] = 2;
        nbRest += 1;
        sandLocation[0] = source;
        sandLocation[1] = 0;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The units of sand come to rest before sand starts flowing into the abyss: "
                << nbRest << std::endl;
    return 0;
}