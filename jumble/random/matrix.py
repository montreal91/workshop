
A = [[1, 2, 3], [4, 5, 6]]
B = [[1, 0], [0, 2]]

def MultiplyMatrices(mA, mB):
    res = [[0 for i in range(len(mB[0]))] for j in range(len(mA))]
    for i in range(len(mA)):
        for j in range(len(mB[0])):
            for k in range(len(mB)):
                res[i][j] += mA[i][k] * mB[k][j]
    return res

def PrintMatrix(mA):
    for row in mA:
        for el in row:
            print("{0:5.2f} ".format(el), end=" ")
        print()

if __name__ == '__main__':
     PrintMatrix(MultiplyMatrices(B, A)) 
     # PrintMatrix(MultiplyMatrices(A, B)) 
