import time

def checkIfConnect(cubeone, cubetwo):
    if (cubeone[0] == cubetwo[0] and cubeone[1] == cubetwo[1] and abs(cubeone[2] - cubetwo[2]) == 1) or \
        (cubeone[1] == cubetwo[1] and cubeone[2] == cubetwo[2] and abs(cubeone[0] - cubetwo[0]) == 1) or \
        (cubeone[0] == cubetwo[0] and cubeone[2] == cubetwo[2] and abs(cubeone[1] - cubetwo[1]) == 1):
        return True
    return False

def main():
    start_time = time.time()
    surfaceArea = 0
    cubes = []
    
    TXT_FILE = 'Data/Q18.txt'

    with open(TXT_FILE) as f:
        while True:
            line = f.readline()
            if not line:
                break
            
            newCube = [int(i) for i in line[:-1].split(',')] + [6]
            
            for cubenb, cube in enumerate(cubes):
                if checkIfConnect(newCube, cube):
                    cubes[cubenb][3] -= 1
                    surfaceArea -= 1
                    if cubes[cubenb][3] == 0:
                        cubes.remove(cubes[cubenb])
                    newCube[3] -= 1
            if newCube[3] > 0:
                cubes.append(newCube)
                surfaceArea += newCube[3]
    
    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The surface area of scanned lava droplet: {surfaceArea}')
    
if __name__ == '__main__':
    main()