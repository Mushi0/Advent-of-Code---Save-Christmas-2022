import time

class Node:
    def __init__(self, name, data):
        self.name = name
        self.data = data
        self.children = []
        self.parent = None
    
    def createChild(self, child):
        self.children.append(child)
        child.parent = self
    
    def findChild(self, childName):
        for child in self.children:
            if child.name == childName:
                return child
    
    def returnSize(self):
        size = self.data
        for child in self.children:
            size += child.returnSize()
        return size

def findDirToDelete(spaceToDelete, thisNode):
    dirToDelete = float('inf')
    thisSize = thisNode.returnSize()
    if (thisSize > spaceToDelete) and (thisSize < dirToDelete):
        dirToDelete = thisSize
    for child in thisNode.children:
        childDirToDelete = findDirToDelete(spaceToDelete, child)
        if dirToDelete > childDirToDelete:
            dirToDelete = childDirToDelete
    return dirToDelete

def main():
    start_time = time.time()
    
    TXT_FILE = 'Data/Q7.txt'
    totalSpace = 70000000
    spaceNeeded = 30000000
    
    with open(TXT_FILE) as f:
        f.readline()
        root = Node('/', 0)
        thisNode = root
        while True:
            line = f.readline()
            if not line:
                break
            command = line[:-1].split(' ')
            if command[0] == '$':
                if command[1] == 'cd':
                    if command[2] == '..':
                        thisNode = thisNode.parent
                    else:
                        thisNode = thisNode.findChild(command[2])
            else:
                if command[0] == 'dir':
                    newDir = Node(command[1], 0)
                    thisNode.createChild(newDir)
                else:
                    newFile = Node(command[1], int(command[0]))
                    thisNode.createChild(newFile)

    spaceToDelete = spaceNeeded - (totalSpace - root.returnSize())
    dirToDelete = findDirToDelete(spaceToDelete, root)
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The size of the directory needed to delete: {dirToDelete}')

if __name__ == '__main__':
    main()