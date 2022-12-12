import time
import collections

def main():
    start_time = time.time()
    
    TXT_FILE = 'Data/Q12.txt'

    map = []
    with open(TXT_FILE) as f:
        while True:
            line = f.readline()
            if not line:
                break
            line = list(line[:-1])
            map.append(line)
    
    M = len(map)
    N = len(map[0])

    elevation = [[0]*N for i in range(M)]
    for i in range(M):
        for j in range(N):
            if map[i][j] == 'S':
                elevation[i][j] = 1
                start = [i, j]
            elif map[i][j] == 'E':
                elevation[i][j] = 26
            else:
                elevation[i][j] = ord(map[i][j]) - ord('a') + 1
    
    stepsToVisit = collections.deque()
    stepsToVisit.append((start, 0))
    stepsVisited = set()
    while stepsToVisit:
        [m, n], d = stepsToVisit.popleft()
        if (m, n) in stepsVisited:
            continue
        stepsVisited.add((m, n))
        if map[m][n] == 'E':
            print(f'The fewest steps required to move to get the best signal: {d}')
            break
        for (addm, addn) in [(0, 1), (-1, 0), (0, -1), (1, 0)]:
            mm = m + addm
            nn = n + addn
            if 0 <= mm < M and 0 <= nn < N and elevation[mm][nn] <= elevation[m][n] + 1:
                stepsToVisit.append(([mm, nn], d + 1))

    print(f'Time taken: {(time.time() - start_time):.3e}s')

if __name__ == '__main__':
    main()