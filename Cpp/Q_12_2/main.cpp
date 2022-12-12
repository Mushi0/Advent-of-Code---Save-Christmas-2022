#include <fstream>
#include <iostream>
#include <array>
#include <deque>
#include <vector>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q12.txt"};
int nbRows{41};
int nbColumns{161};

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    char map[nbRows][nbColumns]{};
    int elevation[nbRows][nbColumns]{0};
    char c;
    std::array<int, 3> endLocation{0};

    for(int i = 0; i < nbRows; i++){
        for(int j = 0; j < nbColumns; j++){
            myInputFile >> c;
            map[i][j] = c;
            if(c == 'S'){
                elevation[i][j] = 1;
            }else if(c == 'E'){
                elevation[i][j] = 26;
                endLocation[0] = i; endLocation[1] = j;
            }else{
                elevation[i][j] = int(c) - int('a') + 1;
            }
        }
    }

    std::deque<std::array<int, 3>> stepsToVisit;
    stepsToVisit.push_back(endLocation);
    std::vector<std::array<int, 2>> stepsVisited;
    int directios[4][2]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while(!stepsToVisit.empty()){
        std::array<int, 3> thisLocation{stepsToVisit.front()};
        stepsToVisit.pop_front();
        int row{thisLocation[0]}; int column{thisLocation[1]};
        int distance{thisLocation[2]};

        bool found{false};
        for(int i = 0; i < stepsVisited.size(); i++){
            if((stepsVisited[i][0] == row) and (stepsVisited[i][1] == column)){
                found = true;
                break;
            }
        }
        if(found){
            continue;
        }
        stepsVisited.push_back({row, column});

        if(elevation[row][column] == 1){
            std::cout << "The fewest steps required to move to get the best signal: " 
                        << distance << std::endl;
            break;
        }

        for(int i = 0; i < 4; i++){
            int newRow = row + directios[i][0];
            int newColumn = column + directios[i][1];
            if((newRow >= 0) and (newRow < nbRows) and 
                (newColumn >= 0) and (newColumn < nbColumns) and 
                elevation[newRow][newColumn] >= elevation[row][column] - 1){
                stepsToVisit.push_back({newRow, newColumn, distance + 1});
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    return 0;
}