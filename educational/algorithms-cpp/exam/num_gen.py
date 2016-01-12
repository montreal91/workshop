
import sys
from random import randint

def GenerateBigNum(length):
    res = ""
    for i in range(length):
        res += str(randint(0, 9))
    return res

if __name__ == '__main__':
    print(GenerateBigNum(int(sys.argv[1])))
