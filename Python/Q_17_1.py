import time
from itertools import cycle

def main():
    start_time = time.time()
    
    TXT_FILE = 'Data/Q17.txt'
    maxNbRocks = 2022
    mapWide = 7

    rocks = cycle([[[0, 0, 1, 1, 1, 1, 0], [0, 0, 1, 1, 1, 1, 0]], 
                [[0, 0, 2, 1, 2, 0, 0], [0, 0, 2, 3, 2, 0, 0]], 
                [[0, 0, 1, 1, 1, 0, 0], [0, 0, 1, 1, 3, 0, 0]], 
                [[0, 0, 1, 0, 0, 0, 0], [0, 0, 4, 0, 0, 0, 0]], 
                [[0, 0, 1, 1, 0, 0, 0], [0, 0, 2, 2, 0, 0, 0]]])
    
    def move(direction, rock):
        newRock = rock
        if direction == '>' and rock[0][-1] == 0:
            newRock = [[0] + rock[0][:-1], [0] + rock[1][:-1]]
        elif direction == '<' and rock[0][0] == 0:
            newRock = [rock[0][1:] + [0], rock[1][1:] + [0]]
        return newRock
    
    def checkIfTouchVer(rockBot, mapTop):
        touch = False
        for pixel in range(mapWide):
            if rockBot[pixel] == (mapTop[pixel] + 1):
                touch = True
                break
        return touch

    def checkIfTouchHor(direction, rockBot, mapTop):
        touch = False
        if direction == '>':
            for pixel in range(mapWide - 1):
                if rockBot[pixel] != 0 and rockBot[pixel] <= mapTop[pixel + 1]:
                    touch = True
                    break
        elif direction == '<':
            for pixel in range(1, mapWide):
                if rockBot[pixel] != 0 and rockBot[pixel] <= mapTop[pixel - 1]:
                    touch = True
                    break
        return touch

    with open(TXT_FILE) as f:
        hotGas = f.read()
    hotGas = cycle(hotGas)

    nbRocks = 0
    mapTop = [0, 0, 0, 0, 0, 0, 0]
    while(nbRocks < maxNbRocks):
        rock = next(rocks)
        maxHight = max(mapTop)
        rock = [[pixel + maxHight if pixel != 0 else 0 for pixel in line] 
                    for line in rock]
        
        for _ in range(4):
            direction = next(hotGas)
            rock = move(direction, rock)

        while(not checkIfTouchVer(rock[0], mapTop)):
            rock = [[pixel - 1 if pixel != 0 else 0 for pixel in line] 
                        for line in rock]
            direction = next(hotGas)
            if(not checkIfTouchHor(direction, rock[0], mapTop)):
                rock = move(direction, rock)

        mapTop = [max(mapTop[pixel], rock[1][pixel]) 
                    for pixel in range(mapWide)]
        nbRocks += 1
    
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The height of the wall after {maxNbRocks} rocks: {max(mapTop)}')
    
if __name__ == '__main__':
    main()