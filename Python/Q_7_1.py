class Node:
    def __init__(self, name, data):
        self.name = name
        self.data = data
        self.children = []
        self.parent = None
        self.left = None
        self.right = None
    
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

def addTotalSize(maxSize, thisNode):
    totalSize = 0
    thisSize = thisNode.returnSize()
    if thisSize < maxSize:
        totalSize += thisSize
    for child in thisNode.children:
        if child.children != []:
            totalSize += addTotalSize(maxSize, child)
    return totalSize

def main():
    TXT_FILE = 'Data/Q7.txt'
    maxSize = 100000

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

    totalSize = addTotalSize(maxSize, root)
    print(f'The sum of the total sizes of directories \
            \nwith a total size of at most 100000: {totalSize}')

if __name__ == '__main__':
    main()