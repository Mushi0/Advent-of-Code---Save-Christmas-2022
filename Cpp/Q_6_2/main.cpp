#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <chrono>

std::ifstream myInputFile{"../../Data/Q6.txt"};

void readSignal(std::queue<char>& signalBuffer, char signal){
        signalBuffer.push(signal);
        signalBuffer.pop();
}

bool detectStartSignal(std::queue<char> signalBuffer){
    unsigned long int signalBufferSize{signalBuffer.size()};
    char signalBufferChr[signalBufferSize];
    for(int i = 0; i < signalBufferSize; i++){
        signalBufferChr[i] = signalBuffer.front();
        signalBuffer.pop();
    }
    for(int i = 0; i < signalBufferSize; i++){
        for(int j = i + 1; j < signalBufferSize; j++){
            if(signalBufferChr[i] == signalBufferChr[j]) return false;
        }
    }
    return true;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    int nbStartOfPacket{14};
    std::string myText;
    std::queue<char> signalBuffer;

    myInputFile >> myText;

    for(int i = 0; i < nbStartOfPacket; i++){
        signalBuffer.push(myText[i]);
    }
    int characterCoung{nbStartOfPacket};
    for(int i = nbStartOfPacket; i < myText.length(); i++){
        if(detectStartSignal(signalBuffer)){
            break;
        }
        readSignal(signalBuffer, myText[i]);
        characterCoung += 1;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count()*1e-6 << "s\n";
    std::cout << "The number of characters need to be processed \
                \n before the first start-of-packet marker is detected: " 
                << characterCoung << std::endl;
    return 0;
}