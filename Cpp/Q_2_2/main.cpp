#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

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
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream myInputFile{"..\\..\\Data\\Q2.txt"};
    std::string myText;
    char myMove{};
    char theirMove{};
    int totalScore{0};

    while(std::getline(myInputFile, myText)){
        theirMove = myText[0];
        myMove = myText[2];
        totalScore += (shapeScore(myMove, theirMove) + resultScore(myMove));
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "My total score is: " << totalScore;
    return 0;
}