#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

std::ifstream myInputFile{"..\\..\\Data\\Q7.txt"};

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
    int data;
    struct node *parent;
    std::vector<node*> children;
};

node* createNode(std::string name, int data){
    node* newNode = new node();
    newNode->name = name;
    newNode->data = data;
    return newNode;
}

void addChild(node* thisNode, node* childNode){
    thisNode->children.push_back(childNode);
    childNode->parent = thisNode;
}

node* findChild(node* thisNode, std::string childName){
    for(int i = 0; i < thisNode->children.size(); i++){
        node* child = thisNode->children[i];
        if(child->name == childName){
            return child;
        }
    }
    return 0;
}

int returnSize(node* thisNode){
    int size = thisNode->data;
    for(int i = 0; i < thisNode->children.size(); i++){
        node* child = thisNode->children[i];
        size += returnSize(child);
    }
    return size;
}

int addTotalSize(int maxSize, node* thisNode){
    int totalSize{0};
    int thisSize = returnSize(thisNode);
    if(thisSize < maxSize){
        totalSize += thisSize;
    }
    for(int i = 0; i < thisNode->children.size(); i++){
        node* child = thisNode->children[i];
        if(!child->children.empty()){
            totalSize += addTotalSize(maxSize, child);
        }
    }
    return totalSize;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    std::string myText;
    int maxSize{100000};

    node* root = createNode("/", 0);
    node* thisNode = root;
    
    std::getline(myInputFile, myText);
    while(std::getline(myInputFile, myText)){
        std::vector<std::string> command = strsplit(myText, ' ');
        if(command[0] == "$"){
            if(command[1] == "cd"){
                if(command[2] == ".."){
                    thisNode = thisNode->parent;
                }else{
                    thisNode = findChild(thisNode, command[2]);
                }
            }
        }else{
            if(command[0] == "dir"){
                node* newDir = createNode(command[1], 0);
                addChild(thisNode, newDir);
            }else{
                node* newFile = createNode(command[1], std::stoi(command[0]));
                addChild(thisNode, newFile);
            }
        }
    }

    int totalSize = addTotalSize(maxSize, root);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The sum of the total sizes of directories \
                \n with a total size of at most 100000: " 
                << totalSize << std::endl;
    return 0;
}