#include <fstream>
#include <iostream>
#include <string>
#include <queue>

std::ifstream myInputFile{"../../Data/Q6.txt"};

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
    int nbStartOfPacket{14};
    std::string myText;
    std::queue<char> signalBuffer;

    if(!myInputFile){
        std::cerr << "Uh oh, file could not be opened for reading!\n";
        return 1;
    }else{
        myInputFile >> myText;
    }

    for(int i = 0; i < nbStartOfPacket; i++){
        signalBuffer.push(myText[i]);
    }
    int characterCoung{nbStartOfPacket};
    for(int i = nbStartOfPacket; i < myText.length(); i++){
        if(detectStartSignal(signalBuffer)){
            break;
        }
        signalBuffer.push(myText[i]);
        signalBuffer.pop();
        characterCoung += 1;
    }

    std::cout << "The number of characters need to be processed \
                \n before the first start-of-packet marker is detected: " 
                << characterCoung << std::endl;
    
    return 0;
}