#include <fstream>
#include <iostream>
#include <string>

int main(){
    std::ifstream myInputFile{"..\\..\\Data\\Q1.txt"};
    std::string myText;
    int calories{0};
    int mostCalories{0};
    
    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    while(myInputFile){
        std::getline(myInputFile, myText);
        if(myText.empty()){
            if(mostCalories < calories){
                mostCalories = calories;
            }
            calories = 0;
        }
        else{
            calories += stoi(myText);
        }
    }

    std::cout << "The most calories is: " << mostCalories;
    
    return 0;
}