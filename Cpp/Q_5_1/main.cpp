#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

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
    for(int i = 0; i < quantity; i++){
        myStacks[toStack].push(myStacks[fromStack].top());
        myStacks[fromStack].pop();
    }
}

int main(){
    std::string myText;
    std::string topOfStacks;

    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

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

    std::cout << "The top of the stacks: " << topOfStacks << std::endl;
    
    return 0;
}