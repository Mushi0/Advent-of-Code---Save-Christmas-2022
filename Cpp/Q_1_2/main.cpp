#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <time.h>
#include <iomanip>

int main(){
    clock_t tStart = clock();

    std::ifstream myInputFile{"..\\..\\Data\\Q1.txt"};
    std::string myText;
    int calories{0};
    int calories_list[254];
    int count{0};
    
    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    while(myInputFile){
        std::getline(myInputFile, myText);
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

    std::cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s\n";
    std::cout << "The total of the largest three calories is: " << calories_list[0] + calories_list[1] + calories_list[2];
    return 0;
}