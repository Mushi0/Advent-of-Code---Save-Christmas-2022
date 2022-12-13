import time
import collections

def checkIfRight(firstList, secondList):
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
        checkItem = checkIfRight(firstItem, secondItem)
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

    pairNb = 1
    sumOfIndices = 0
    with open(TXT_FILE) as f:
        while True:
            line = f.readline()
            if not line:
                break
            firstList = eval(line)
            line = f.readline()
            secondList = eval(line)
            f.readline()
            
            if checkIfRight(firstList, secondList) >= 1:
                sumOfIndices += pairNb
            
            pairNb += 1
    
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The sum of the indices of right pairs: {sumOfIndices}')

if __name__ == '__main__':
    main()