import time
from functools import lru_cache

class Node():
    def __init__(self, name, flowRate = 0):
        self.name = name
        self.flowRate = flowRate
        self.connections = []
    
    def copy(self):
        newNode = Node(self.name, self.flowRate)
        newNode.connections = self.connections
        return newNode

def main():
    start_time = time.time()
    
    TXT_FILE = 'Data/Q16.txt'
    totalTime = 26

    nodes = []
    with open(TXT_FILE) as f:
        while True:
            line = f.readline()
            if not line:
                break
            line = line[:-1].split(' ')
            newNode = Node(line[1], int(line[4][5:-1]))
            for connection in line[9:]:
                if not connection == line[-1]:
                    connection = connection[:-1]
                newNode.connections.append(connection)
            nodes.append(newNode)

    def findNode(nodeName):
        for node in nodes:
            if node.name == nodeName:
                return node
    
    @lru_cache(maxsize = None)
    def returnBestMove(myNode, elephantNode, opened, minRemain):
        if minRemain <= 0:
            return 0
        best = 0
        if myNode.name == elephantNode.name:
            presRelIfOpen = (minRemain - 1)*myNode.flowRate
            currentOpened = tuple(opened + (myNode.name, ))
            for myNeighbour in myNode.connections:
                myNeighbourNode = findNode(myNeighbour)
                if myNode.name not in opened and presRelIfOpen != 0:
                    # the elephant open this node
                    best = max(best, 
                                presRelIfOpen + 
                                returnBestMove(myNeighbourNode, 
                                                elephantNode, 
                                                currentOpened, 
                                                minRemain - 1))
                for elephantNeighbour in elephantNode.connections:
                    elephantNeighbourNode = findNode(elephantNeighbour)
                    # not open this node
                    best = max(best, returnBestMove(myNeighbourNode, 
                                                    elephantNeighbourNode, 
                                                    opened, 
                                                    minRemain - 1))
        else:
            presRelIfOpenMine = (minRemain - 1)*myNode.flowRate
            currentOpenedMine = tuple(opened + (myNode.name, ))
            presRelIfOpenEl = (minRemain - 1)*elephantNode.flowRate
            currentOpenedEl = tuple(opened + (elephantNode.name, ))
            currentOpenedBoth = tuple(opened + (myNode.name, elephantNode.name, ))
            for myNeighbour in myNode.connections:
                myNeighbourNode = findNode(myNeighbour)
                for elephantNeighbour in elephantNode.connections:
                    elephantNeighbourNode = findNode(elephantNeighbour)
                    if myNode.name not in opened and presRelIfOpenMine != 0 and \
                        elephantNode.name not in opened and presRelIfOpenEl != 0:
                        # we both open our nodes
                        best = max(best, 
                            presRelIfOpenMine + presRelIfOpenEl + 
                            returnBestMove(myNeighbourNode, 
                                            elephantNeighbourNode, 
                                            currentOpenedBoth, 
                                            minRemain - 2))
                    # we both don't open
                    best = max(best, 
                        returnBestMove(myNeighbourNode, 
                                        elephantNeighbourNode, 
                                        opened, 
                                        minRemain - 1))
                if elephantNode.name not in opened and presRelIfOpenEl != 0:
                    # only elephantNode open his/hers
                    best = max(best, 
                        presRelIfOpenEl + 
                        returnBestMove(myNeighbourNode, 
                                        elephantNode, 
                                        currentOpenedEl, 
                                        minRemain - 1))
            for elephantNeighbour in elephantNode.connections:
                elephantNeighbourNode = findNode(elephantNeighbour)
                # only I open mine
                if myNode.name not in opened and presRelIfOpenMine != 0:
                    best = max(best, 
                            presRelIfOpenMine + 
                            returnBestMove(myNode, 
                                            elephantNeighbourNode, 
                                            currentOpenedMine, 
                                            minRemain - 1))
        return best
    
    best = returnBestMove(findNode('AA'), findNode('AA'), (), totalTime)
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The most pressure one can release: {best}')
    
if __name__ == '__main__':
    main()