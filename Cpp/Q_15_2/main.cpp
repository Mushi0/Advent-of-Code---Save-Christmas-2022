#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

std::ifstream myInputFile{"../../Data/Q15.txt"};
int maxSize{4000000};

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
    std::string tuningFrequency;

    while(myInputFile){
        myInputFile >> sensor.x;
        myInputFile >> sensor.y;
        myInputFile >> beacon.x;
        myInputFile >> beacon.y;
        sensors.push_back(sensor);
        distance = std::abs(sensor.x - beacon.x) + std::abs(sensor.y - beacon.y);
        distances.push_back(distance);
    }

    bool fond{false};
    for(int sensornb = 0; sensornb < sensors.size(); sensornb++){
        for(int y = sensors[sensornb].y - distances[sensornb] - 1;
                y <= sensors[sensornb].y + distances[sensornb] + 1;
                y++){
            if(y >= 0 && y <= maxSize){
                if((y == sensors[sensornb].y - distances[sensornb] - 1) || 
                        (y == sensors[sensornb].y + distances[sensornb] + 1)){
                    int x = sensors[sensornb].x;
                    if(x >= 0 && x <= maxSize){
                        fond = true;
                        for(int checksensor = 0; checksensor < sensors.size(); checksensor++){
                            if((checksensor != sensornb) && 
                                    (std::abs(x - sensors[checksensor].x) + 
                                    std::abs(y - sensors[checksensor].y) 
                                    <= distances[checksensor])){
                                fond = false;
                                break;
                            }
                        }
                        if(fond){
                            tuningFrequency = std::to_string(x*4) + std::to_string(y);
                            break;
                        }
                    }
                }else{
                    int xs[2]{sensors[sensornb].x - \
                            distances[sensornb] + \
                            std::abs(y - sensors[sensornb].y) - 1, 
                            sensors[sensornb].x + \
                            distances[sensornb] - \
                            std::abs(y - sensors[sensornb].y) + 1};
                    for(int i = 0; i <= 1; i++){
                        int x = xs[i];
                        if(x >= 0 && x <= maxSize){
                            fond = true;
                            for(int checksensor = 0; checksensor < sensors.size(); checksensor++){
                                if((checksensor != sensornb) && 
                                        ((std::abs(x - sensors[checksensor].x) + 
                                        std::abs(y - sensors[checksensor].y) 
                                        <= distances[checksensor]))){
                                    fond = false;
                                    break;
                                }
                            }
                            if(fond){
                                tuningFrequency = std::to_string(x*4) + std::to_string(y);
                                break;
                            }
                        }
                    }
                    if(fond){
                        break;
                    }
                }
            }
        }
        if(fond){
            break;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The tuning frequency of the only possible position: " << tuningFrequency << std::endl;
    return 0;
}