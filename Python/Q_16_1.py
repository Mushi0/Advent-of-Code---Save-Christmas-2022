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
    totalTime = 30

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
    def returnBestMove(thisNode, opened, minRemain):
        if minRemain <= 0:
            return 0
        best = 0
        pressureReleaseIfOpen = (minRemain - 1)*thisNode.flowRate
        currentOpened = tuple(opened + (thisNode.name, ))
        for neighbour in thisNode.connections:
            neighbourNode = findNode(neighbour)
            if thisNode.name not in opened and pressureReleaseIfOpen != 0:
                # open this node
                best = max(best, 
                    pressureReleaseIfOpen + returnBestMove(neighbourNode, 
                                                            currentOpened, 
                                                            minRemain - 2))
            # not open this node
            best = max(best, returnBestMove(neighbourNode, 
                                            opened, 
                                            minRemain - 1))
        return best
    
    best = returnBestMove(findNode('AA'), (), totalTime)
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The most pressure one can release: {best}')
    
if __name__ == '__main__':
    main()