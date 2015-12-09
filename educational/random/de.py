A = {0: 1.0, 1: 0.0}

def GetBByIndex(n):
    prod = 1
    for i in range( 1, n + 1 ):
        prod *= i
    return 1 / prod

def SumInnerSeq(n):
    sum = 0
    for m in range(n):
        sum += A[n-m] * GetBByIndex(m)
    return sum

def ComputeAAtIndex(n):
    if n in A:
        return A[n]
    elif n == 2:
        return A[0] * GetBByIndex(0) / 10
    elif n == 3:
        return (A[2] * 30 - A[1]*GetBByIndex(0) - A[0]*GetBByIndex(1)) / 36
    else:
        num1 = 5 * (n-1) * (n-2) * A[n-1]
        num2 = (n-2) * (n-3) * A[n-2]
        num3 = 6 * n * (n-1)
        num4 = SumInnerSeq(n-2)
        return (num1 - num2 - num4) / num3

def FillA(n):
    for i in range(n):
        A[i] = ComputeAAtIndex(i)

def PrintAllA(n):
    for i in range(n+1):
        if i in A:
            print( i, "{0:.4f}".format(A[i]))

if __name__ == '__main__':
    FillA(100)
    PrintAllA(100)
