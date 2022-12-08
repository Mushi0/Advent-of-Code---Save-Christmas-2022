#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>

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
    clock_t tStart = clock();

    std::ifstream myInputFile{"../../Data/Q3.txt"};
    std::string myText;
    int totalPriorities{};
    std::string firstCompartment;
    std::string secondCompartment;
    char sameItem{};
    
    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    while(std::getline(myInputFile, myText)){
        long unsigned int n{myText.length()};
        firstCompartment = myText.substr(0, n/2);
        secondCompartment = myText.substr(n/2, n);
        sameItem = findSameItem(firstCompartment, secondCompartment);
        totalPriorities += getPriority(sameItem);
    }

    std::cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s\n";
    std::cout << "The sum of the priorities is: " << totalPriorities << std::endl;
    return 0;
}