#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream myInputFile{"..\\..\\Data\\Q1.txt"};
    std::string myText;
    int calories{0};
    int mostCalories{0};
    
    while(std::getline(myInputFile, myText)){
        if(myText.empty()){
            if(mostCalories < calories){
                mostCalories = calories;
            }
            calories = 0;
        }
        else{
            calories += stoi(myText);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The most calories is: " << mostCalories;
    return 0;
}