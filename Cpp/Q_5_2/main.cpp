#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
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

int main(){
    std::ifstream myInputFile{"../../Data/Q5.txt"};
    std::string myText;
    std::stack<char> myStacks[9];
    std::string topOfStacks;
    std::stack<char> tempStacks;

    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    for(int i = 0; i < 9; i++){
        std::getline(myInputFile, myText);
        for(int j = 0; j < myText.length(); j++){
            myStacks[i].push(myText[j]);
        }
    }
    std::getline(myInputFile, myText);

    while(std::getline(myInputFile, myText)){
        std::vector<std::string> splitedText = strsplit(myText, ' ');
        int quantity = std::stoi(splitedText[1]);
        int fromStack = std::stoi(splitedText[3]) - 1;
        int toStack = std::stoi(splitedText[5]) - 1;
        
        for(int i = 0; i < quantity; i++){
            tempStacks.push(myStacks[fromStack].top());
            myStacks[fromStack].pop();
        }

        for(int i = 0; i < quantity; i++){
            myStacks[toStack].push(tempStacks.top());
            tempStacks.pop();
        }
    }

    for(int i = 0; i < 9; i++){
        topOfStacks += myStacks[i].top();
    }

    std::cout << "The top of the stacks: " << topOfStacks << std::endl;
    
    return 0;
}