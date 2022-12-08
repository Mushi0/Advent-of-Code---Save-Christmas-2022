#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <chrono>

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream myInputFile{"..\\..\\Data\\Q1.txt"};
    std::string myText;
    int calories{0};
    int calories_list[254];
    int count{0};
    
    while(std::getline(myInputFile, myText)){
        if(myText.empty()){
            calories_list[count] = calories;
            calories = 0;
            count++;
        }else{
            calories += stoi(myText);
        }
    }

    int n = sizeof(calories_list) / sizeof(calories_list[0]);
    std::sort(calories_list, calories_list + n, std::greater<int>());

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The total of the largest three calories is: " << calories_list[0] + calories_list[1] + calories_list[2];
    return 0;
}