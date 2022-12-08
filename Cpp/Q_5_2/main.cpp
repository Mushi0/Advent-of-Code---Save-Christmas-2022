#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <chrono>

std::ifstream myInputFile{"../../Data/Q5.txt"};
int nbStacks{9};

std::vector<std::string> strsplit(std::string strToSplit, char delimeter){
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while(std::getline(ss, item, delimeter)){
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

void createStacks(std::stack<char>* myStacks){
    std::string myText;
    for(int i = 0; i < nbStacks; i++){
        std::getline(myInputFile, myText);
        for(int j = 0; j < myText.length(); j++){
            myStacks[i].push(myText[j]);
        }
    }
    std::getline(myInputFile, myText);
}

void moveStacks(std::stack<char>* myStacks, int quantity, int fromStack, int toStack){
    std::stack<char> tempStacks;
    for(int i = 0; i < quantity; i++){
        tempStacks.push(myStacks[fromStack].top());
        myStacks[fromStack].pop();
    }

    for(int i = 0; i < quantity; i++){
        myStacks[toStack].push(tempStacks.top());
        tempStacks.pop();
    }
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    std::string myText;
    std::string topOfStacks;
    std::stack<char> myStacks[nbStacks];
    createStacks(myStacks);

    while(std::getline(myInputFile, myText)){
        std::vector<std::string> splitedText = strsplit(myText, ' ');
        int quantity = std::stoi(splitedText[1]);
        int fromStack = std::stoi(splitedText[3]) - 1;
        int toStack = std::stoi(splitedText[5]) - 1;
        moveStacks(myStacks, quantity, fromStack, toStack);
    }

    for(int i = 0; i < nbStacks; i++){
        topOfStacks += myStacks[i].top();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The top of the stacks: " << topOfStacks << std::endl;
    return 0;
}