#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

std::vector<std::string> strsplit(std::string strToSplit, char delimeter){
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while(std::getline(ss, item, delimeter)){
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

int isoverlaped(int a[], int b[]){
    if((a[1] < b[0]) || (a[0] > b[1])){
        return 0;
    }
    return 1;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream myInputFile{"../../Data/Q4.txt"};
    std::string myText;
    int nbOverlapedPairs{0};
    
    while(std::getline(myInputFile, myText)){
        std::vector<std::string> splitedText = strsplit(myText, ',');
        std::vector<std::string> firstElf = strsplit(splitedText[0], '-');
        std::vector<std::string> secondElf = strsplit(splitedText[1], '-');
        int firstElfInt[2] = {std::stoi(firstElf[0]), std::stoi(firstElf[1])};
        int secondElfInt[2] = {std::stoi(secondElf[0]), std::stoi(secondElf[1])};
        nbOverlapedPairs += isoverlaped(firstElfInt, secondElfInt);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The number of the assignment pairs where ranges overlap: " << nbOverlapedPairs << std::endl;
    return 0;
}