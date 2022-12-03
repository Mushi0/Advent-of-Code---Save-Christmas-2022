#include <fstream>
#include <iostream>
#include <string>

int resultScore(char move){
    switch(move){
        case 'X':
            return 0;
        case 'Y':
            return 3;
        case 'Z':
            return 6;
    }
    return 0;
}

int shapeScore(char myMove, char theirMove){
    switch(theirMove){
        case 'A':
            switch(myMove){
                case 'X':
                    return 3;
                case 'Y':
                    return 1;
                case 'Z':
                    return 2;
            }
        case 'B':
            switch(myMove){
                case 'X':
                    return 1;
                case 'Y':
                    return 2;
                case 'Z':
                    return 3;
            }
        case 'C':
            switch(myMove){
                case 'X':
                    return 2;
                case 'Y':
                    return 3;
                case 'Z':
                    return 1;
            }
    }
    return 0;
}

int main(){
    std::ifstream myInputFile{"..\\..\\Data\\Q2.txt"};
    std::string myText;
    char myMove{};
    char theirMove{};
    int totalScore{0};

    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }

    while(std::getline(myInputFile, myText)){
        theirMove = myText[0];
        myMove = myText[2];
        totalScore += (shapeScore(myMove, theirMove) + resultScore(myMove));
    }

    std::cout << "My total score is: " << totalScore;

    return 0;
}