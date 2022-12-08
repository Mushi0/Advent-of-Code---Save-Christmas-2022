#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <time.h>
#include <iomanip>

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

int findDirToDelete(int spaceToDelete, node* thisNode){
    int dirToDelete{std::numeric_limits<int>::max()};
    int thisSize = returnSize(thisNode);
    if((thisSize > spaceToDelete) && (thisSize < dirToDelete)) dirToDelete = thisSize;
    for(int i = 0; i < thisNode->children.size(); i++){
        node* child = thisNode->children[i];
        int childDirToDelete = findDirToDelete(spaceToDelete, child);
        if(childDirToDelete < dirToDelete) dirToDelete = childDirToDelete;
    }
    return dirToDelete;
}

int main(){
    clock_t tStart = clock();

    std::string myText;
    int totalSpace{70000000};
    int spaceNeeded{30000000};

    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

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

    int spaceToDelete = spaceNeeded - (totalSpace - returnSize(root));
    int dirToDelete = findDirToDelete(spaceToDelete, root);
    
    std::cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s\n";
    std::cout << "The size of the directory needed to delete: " 
                << dirToDelete << std::endl;
    return 0;
}