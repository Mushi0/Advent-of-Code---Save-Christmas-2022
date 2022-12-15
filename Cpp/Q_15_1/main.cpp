#include <fstream>
#include <iostream>
#include <set>
#include <chrono>

std::ifstream myInputFile{"../../Data/Q15.txt"};
int targetRow{2000000};
std::set<int> setPosNotBeacon;

struct coord{
    int x{0};
    int y{0};
};

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    coord sensor{0, 0};
    coord beacon{0, 0};
    int distance{0};

    while(myInputFile){
        myInputFile >> sensor.x;
        myInputFile >> sensor.y;
        myInputFile >> beacon.x;
        myInputFile >> beacon.y;

        distance = std::abs(sensor.x - beacon.x) + std::abs(sensor.y - beacon.y);

        if(std::abs(sensor.y - targetRow) <= distance){
            for(int pos = sensor.x - (distance - std::abs(targetRow - sensor.y)); 
                    pos <= sensor.x + (distance - std::abs(targetRow - sensor.y));
                    pos++){
                    setPosNotBeacon.insert(pos);
                }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The number of positions cannot contain a beacon in row " 
                << targetRow << ": " << setPosNotBeacon.size() - 1 << std::endl;
    return 0;
}