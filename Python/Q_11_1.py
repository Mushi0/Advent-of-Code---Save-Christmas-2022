import time
import math
# from tqdm import tqdm

class monkey:
    def __init__(self, items, operation, operand, divisor, resultTrue, resultFalse):
        self.items = items
        self.operation = operation
        self.operand = operand
        self.divisor = divisor
        self.resultTrue = resultTrue
        self.resultFalse = resultFalse
        self.nbInspects = 0

def main():
    start_time = time.time()
    nbRounds = 20
    
    monkeys = []
    newMonkey = monkey([54, 82, 90, 88, 86, 54], '*', 7, 11, 2, 6)
    monkeys.append(newMonkey)
    newMonkey = monkey([91, 65], '*', 13, 5, 7, 4)
    monkeys.append(newMonkey)
    newMonkey = monkey([62, 54, 57, 92, 83, 63, 63], '+', 1, 7, 1, 7)
    monkeys.append(newMonkey)
    newMonkey = monkey([67, 72, 68], '^', 2, 2, 0, 6)
    monkeys.append(newMonkey)
    newMonkey = monkey([68, 89, 90, 86, 84, 57, 72, 84], '+', 7, 17, 3, 5)
    monkeys.append(newMonkey)
    newMonkey = monkey([79, 83, 64, 58], '+', 6, 13, 3, 0)
    monkeys.append(newMonkey)
    newMonkey = monkey([96, 72, 89, 70, 88], '+', 4, 3, 1, 2)
    monkeys.append(newMonkey)
    newMonkey = monkey([79], '+', 8, 19, 4, 5)
    monkeys.append(newMonkey)
    
    for roundnb in range(nbRounds):
        for thisMonkey in monkeys:
            for item in thisMonkey.items:
                if thisMonkey.operation == '+':
                    item += thisMonkey.operand
                elif thisMonkey.operation == '*':
                    item *= thisMonkey.operand
                elif thisMonkey.operation == '^':
                    item *= item
                
                item = math.floor(item/3)
                thisMonkey.nbInspects += 1
                
                if item % thisMonkey.divisor == 0:
                    monkeys[thisMonkey.resultTrue].items += [item]
                else:
                    monkeys[thisMonkey.resultFalse].items += [item]
            thisMonkey.items = []
    
    inspects = []
    for thisMonkey in monkeys:
        inspects.append(thisMonkey.nbInspects)
    inspects.sort(reverse = True)

    print(f'Time taken: {(time.time() - start_time):.3e}s')
    print(f'The level of monkey business after 20 rounds: {inspects[0]*inspects[1]}')

if __name__ == '__main__':
    main()