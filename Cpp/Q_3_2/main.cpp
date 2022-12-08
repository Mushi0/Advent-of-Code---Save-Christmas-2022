#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

char findSameItem(std::string a, std::string b, std::string c){
    for(int i = 0; i < a.length(); i++){
        for(int j = 0; j < b.length(); j++){
            for(int k = 0; k < c.length(); k++){
                if(a[i] == b[j] && a[i] == c[k]){
                return a[i];
            }
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
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream myInputFile{"../../Data/Q3.txt"};
    std::string firstElf;
    std::string secondElf;
    std::string thirdElf;
    int totalPriorities{};
    char sameItem{};
    
    while(std::getline(myInputFile, firstElf)){
        std::getline(myInputFile, secondElf);
        std::getline(myInputFile, thirdElf);
        sameItem = findSameItem(firstElf, secondElf, thirdElf);
        totalPriorities += getPriority(sameItem);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The sum of the priorities is: " << totalPriorities << std::endl;
    return 0;
}