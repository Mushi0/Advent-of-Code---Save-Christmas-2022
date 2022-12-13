import time
import collections

def compare(firstList, secondList):
    if (type(firstList) == int) and (type(secondList) == int):
        if firstList < secondList:
            return 1
        elif firstList == secondList:
            return 0
        else:
            return -1
    elif (type(firstList) == int) and (type(secondList) == list):
        firstList = [firstList]
    elif (type(firstList) == list) and (type(secondList) == int):
        secondList = [secondList]
    
    ifRight = 0
    for i, firstItem in enumerate(firstList):
        if i >= len(secondList):
            ifRight = -1
            break
        secondItem = secondList[i]
        checkItem = compare(firstItem, secondItem)
        ifRight = checkItem
        if checkItem == -1 or checkItem == 1:
            break
    
    if ifRight == 0:
        if len(firstList) < len(secondList):
            ifRight = 1
    
    return ifRight

def main():
    start_time = time.time()
    
    TXT_FILE = 'Data/Q13.txt'
    
    dividerPackets = [[[2]], [[6]]]
    indices = [1, 2]

    with open(TXT_FILE) as f:
        while True:
            line = f.readline()
            if not line:
                break
            if not line == '\n':
                newList = eval(line)
                if compare(newList, dividerPackets[1]) >= 1:
                    indices[1] += 1
                    if compare(newList, dividerPackets[0]) >= 1:
                        indices[0] += 1
    
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The decoder key for the distress signal: {indices[0] * indices[1]}')

if __name__ == '__main__':
    main()