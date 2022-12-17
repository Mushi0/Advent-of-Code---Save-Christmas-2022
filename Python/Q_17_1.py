import time
from itertools import cycle
import numpy as np

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
    
    def findMapWallHeight(map):
        for height in range(len(map) - 1, -1, -1):
            if sum(map[height]) > 0:
                return height + 1
        return 0
    
    def move(direction, rock):
        newRock = rock
        if direction == '>' and rock[0][-1] == 0:
            newRock = [[0] + rock[0][:-1], [0] + rock[1][:-1]]
        elif direction == '<' and rock[0][0] == 0:
            newRock = [rock[0][1:] + [0], rock[1][1:] + [0]]
        return newRock
    
    def checkIfTouchVer(rockBot, map):
        touch = False
        for pixel in range(mapWide):
            if  rockBot[pixel] == 1 or map[rockBot[pixel] - 2, pixel] == 1:
                touch = True
                break
        return touch

    def checkIfTouchHor(direction, rock, map):
        touch = False
        if direction == '>':
            for pixel in range(mapWide - 1):
                for height in range(rock[0][pixel] - 1, rock[1][pixel]):
                    if map[height, pixel + 1] == 1:
                        touch = True
                        break
        elif direction == '<':
            for pixel in range(1, mapWide):
                for height in range(rock[0][pixel] - 1, rock[1][pixel]):
                    if map[height, pixel - 1] == 1:
                        touch = True
                        break
        return touch

    with open(TXT_FILE) as f:
        hotGas = f.read()
    hotGas = cycle(hotGas)

    nbRocks = 0
    map = np.zeros([7, mapWide])
    while(nbRocks < maxNbRocks):
        rock = next(rocks)
        maxHeight = findMapWallHeight(map)
        if len(map) < maxHeight + 7:
            map = np.append(map, np.zeros([7, mapWide]), axis = 0)
        rock = [[pixel + maxHeight if pixel != 0 else 0 for pixel in line] 
                    for line in rock]
        
        for _ in range(4):
            direction = next(hotGas)
            rock = move(direction, rock)

        while(not checkIfTouchVer(rock[0], map)):
            rock = [[pixel - 1 if pixel != 0 else 0 for pixel in line] 
                        for line in rock]
            direction = next(hotGas)
            if(not checkIfTouchHor(direction, rock, map)):
                rock = move(direction, rock)

        for pixel in range(mapWide):
            if rock[0][pixel] != 0:
                for height in range(rock[0][pixel] - 1, rock[1][pixel]):
                    map[height, pixel] = 1
        nbRocks += 1
    
    # print('+-------+')
    # for rownb in range(findMapWallHeight(map), -1, -1):
    #     print('|', end = '')
    #     for element in map[rownb]:
    #         if element == 1:
    #             print('#', end = '')
    #         else:
    #             print('.', end = '')
    #     print('|')
    # print('+-------+')
    
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The height of the wall after {maxNbRocks} rocks: {findMapWallHeight(map)}')
    
if __name__ == '__main__':
    main()