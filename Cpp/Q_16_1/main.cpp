#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <array>
#include <chrono>

std::ifstream myInputFile{"../../Data/Q16.txt"};
int totalTime{30};

std::vector<std::string> strsplit(std::string strToSplit, char delimeter){
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while(std::getline(ss, item, delimeter)){
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

struct node{ 
    std::string name;
    int flowRate{0};
    std::vector<node*> connections;
};

node* createNode(std::string name, int flowRate, std::vector<node*>& nodes){
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i]->name == name){
            nodes[i]->flowRate = flowRate;
            return nodes[i];
        }
    }
    node* newNode = new node();
    newNode-> name = name;
    newNode->flowRate = flowRate;
    nodes.push_back(newNode);
    return newNode;
}

bool checkIfConnected(node* thisNode, node* anothernode){
    for(int j = 0; j < thisNode->connections.size(); j++){
        if(thisNode->connections[j]->name == anothernode->name){
            return true;
        }
    }
    return false;
}

int addConnect(node* thisNode, std::string neighbourName, std::vector<node*>& nodes){
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i]->name == neighbourName){
            if(!checkIfConnected(thisNode, nodes[i])){
                thisNode->connections.push_back(nodes[i]);
            }
            if(!checkIfConnected(nodes[i], thisNode)){
                nodes[i]->connections.push_back(thisNode);
            }
            return 0;
        }
    }
    node* neighbour = new node();
    neighbour->name = neighbourName;
    thisNode->connections.push_back(neighbour);
    if(!checkIfConnected(neighbour, thisNode)){
        neighbour->connections.push_back(thisNode);
    }
    nodes.push_back(neighbour);
    return 0;
}

std::array<int, 2> returnBestMove(std::array<int, 2> move, node* thisNode, std::vector<node*>& nodes){
    if(move[0] <= 0){
        return move;
    }
    move[0]--;
    int knownBestMove = move[1] + thisNode->flowRate*move[0];
    for(int i = 0; i < thisNode->connections.size(); i++){
        std::array<int, 2> possibleBestMove = returnBestMove({move[0], move[1]}, 
                                                thisNode->connections[i], nodes);
        if(possibleBestMove[1] > knownBestMove){
            knownBestMove = possibleBestMove[1];
        }
    }
    return {move[0], knownBestMove};
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    std::string oneValve;
    std::vector<node*> nodes;

    while(std::getline(myInputFile, oneValve)){
        std::vector<std::string> splitedValveData = strsplit(oneValve, ' ');

        node* valve = createNode(splitedValveData[1], 
                std::stoi(splitedValveData[4].substr(5, splitedValveData[4].size() - 6)), 
                nodes);
        for(int i = 9; i < splitedValveData.size(); i++){
            if(i == splitedValveData.size() - 1){
                addConnect(valve, splitedValveData[i], nodes);
            }else{
                addConnect(valve, 
                        splitedValveData[i].substr(0, splitedValveData[i].size() - 1), 
                        nodes);
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The most pressure one can release: " 
                << returnBestMove({totalTime, 0}, nodes[0], nodes)[1] << std::endl;
    return 0;
}