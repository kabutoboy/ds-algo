import numpy as np

def matmul(A, B):
    if A.size == 1:
        return np.dot(A, B)
    n = A.shape[0]
    half = int(n/2)
    A11 = A[0:half, 0:half]
    A12 = A[0:half, half:n]
    A21 = A[half:n, 0:half]
    A22 = A[half:n, half:n]
    B11 = B[0:half, 0:half]
    B12 = B[0:half, half:n]
    B21 = B[half:n, 0:half]
    B22 = B[half:n, half:n]
    C11 = matmul(A11, B11) + matmul(A12, B21)
    C12 = matmul(A11, B12) + matmul(A12, B22)
    C21 = matmul(A21, B11) + matmul(A22, B21)
    C22 = matmul(A21, B12) + matmul(A22, B22)
    C = np.zeros((n, n))
    C[0:half, 0:half] = C11
    C[0:half, half:n] = C12
    C[half:n, 0:half] = C21
    C[half:n, half:n] = C22
    return C

total = 0
correct = 0
for i in range(0, 6):
    n = 2**i
    for j in range(0, 10):
        A = np.random.randint(10, size=(n,n))
        B = np.random.randint(10, size=(n,n))
        total += 1
        if (np.array_equal(np.dot(A,B), matmul(A,B))):
            correct += 1

print("correct %d/%d" % (correct, total))
