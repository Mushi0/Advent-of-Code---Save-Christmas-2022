#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <iomanip>

std::vector<std::string> strsplit(std::string strToSplit, char delimeter){
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while(std::getline(ss, item, delimeter)){
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

int iscontained(int a[], int b[]){
    if((a[0] >= b[0] && a[1] <= b[1]) || (a[0] <= b[0] && a[1] >= b[1])){
        return 1;
    }
    return 0;
}

int main(){
    clock_t tStart = clock();

    std::ifstream myInputFile{"../../Data/Q4.txt"};
    std::string myText;
    int nbContainedPairs{0};
    
    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    while(std::getline(myInputFile, myText)){
        std::vector<std::string> splitedText = strsplit(myText, ',');
        std::vector<std::string> firstElf = strsplit(splitedText[0], '-');
        std::vector<std::string> secondElf = strsplit(splitedText[1], '-');
        int firstElfInt[2] = {std::stoi(firstElf[0]), std::stoi(firstElf[1])};
        int secondElfInt[2] = {std::stoi(secondElf[0]), std::stoi(secondElf[1])};
        nbContainedPairs += iscontained(firstElfInt, secondElfInt);
    }

    std::cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s\n";
    std::cout << "The number of the assignment pairs where one range fully contain the other: " << nbContainedPairs << std::endl;
    return 0;
}