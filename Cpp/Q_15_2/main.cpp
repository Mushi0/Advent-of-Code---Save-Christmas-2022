#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

std::ifstream myInputFile{"../../Data/Q15.txt"};
int maxSize{4000000};
int frequencyMult{4000000};

struct coord{
    int x{0};
    int y{0};
};

std::vector<coord> sensors;
std::vector<int> distances;

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    coord sensor{0, 0};
    coord beacon{0, 0};
    int distance{0};
    int tuningFrequency{0};

    while(myInputFile){
        myInputFile >> sensor.x;
        myInputFile >> sensor.y;
        myInputFile >> beacon.x;
        myInputFile >> beacon.y;
        sensors.push_back(sensor);
        distance = std::abs(sensor.x - beacon.x) + std::abs(sensor.y - beacon.y);
        distances.push_back(distance);
    }

    for(int i = 0; i < maxSize; i++){
        for(int j = 0; j < maxSize; j++){
            bool covered{false};
            for(int sensornb = 0; sensornb < sensors.size(); sensornb++){
                if((std::abs(i - sensors[sensornb].x) + std::abs(j - sensors[sensornb].y)) <= distances[sensornb]){
                    covered = true;
                }
            }
            if(!covered){
                tuningFrequency = i*frequencyMult + j;
                break;
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The tuning frequency of the only possible position: " << tuningFrequency << std::endl;
    return 0;
}