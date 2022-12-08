#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

int shapeScore(char move){
    switch(move){
        case 'X':
            return 1;
        case 'Y':
            return 2;
        case 'Z':
            return 3;
    }
    return 0;
}

int resultScore(char myMove, char theirMove){
    switch(myMove){
        case 'X':
            switch(theirMove){
                case 'A':
                    return 3;
                case 'B':
                    return 0;
                case 'C':
                    return 6;
            }
        case 'Y':
            switch(theirMove){
                case 'A':
                    return 6;
                case 'B':
                    return 3;
                case 'C':
                    return 0;
            }
        case 'Z':
            switch(theirMove){
                case 'A':
                    return 0;
                case 'B':
                    return 6;
                case 'C':
                    return 3;
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
        totalScore += (shapeScore(myMove) + resultScore(myMove, theirMove));
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "My total score is: " << totalScore;
    return 0;
}