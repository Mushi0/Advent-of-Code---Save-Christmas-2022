#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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
    std::string myText;
    std::ifstream myInputFile{"../../Data/Q4.txt"};
    int nbOverlapedPairs{0};
    
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
        nbOverlapedPairs += isoverlaped(firstElfInt, secondElfInt);
    }

    std::cout << "The number of the assignment pairs where ranges overlap: " << nbOverlapedPairs << std::endl;
    
    return 0;
}