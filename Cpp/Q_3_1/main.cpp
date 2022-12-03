#include <fstream>
#include <iostream>
#include <string>

char findSameItem(std::string a, std::string b){
    for(int i = 0; i < a.length(); i++){
        for(int j = 0; j < b.length(); j++){
            if(a[i] == b[j]){
                return a[i];
            }
        }
    }
    return 0;
}

int getPriority(char item){
    if(isupper(item)){
        return (int(item) - 38);
    }else{
        return (int(item) - 96);
    }
}

int main(){
    std::string myText;
    std::ifstream myInputFile{"../../Data/Q3.txt"};
    int totalPriorities{};
    std::string firstCompartment;
    std::string secondCompartment;
    char sameItem{};
    
    if(!myInputFile)
    {
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    while(std::getline(myInputFile, myText))
    {
        long unsigned int n{myText.length()};
        firstCompartment = myText.substr(0, n/2);
        secondCompartment = myText.substr(n/2, n);
        sameItem = findSameItem(firstCompartment, secondCompartment);
        totalPriorities += getPriority(sameItem);
    }

    std::cout << "The sum of the priorities is: " << totalPriorities << std::endl;
    
    return 0;
}