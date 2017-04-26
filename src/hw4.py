import numpy as np

def matrix_chain_order(p):
    n = len(p) - 1
    m = np.zeros((n, n), dtype=np.int)
    s = np.zeros((n, n), dtype=np.int)
    for l in range(2, n+1):
        for i in range(0, n-l+1):
            j = i+l-1
            m[i, j] = 999999999
            for k in range(i, j):
                q = m[i, k] + m[k+1, j] + p[i]*p[k+1]*p[j+1]
                if q < m[i, j]:
                    m[i, j] = q
                    s[i, j] = k
    return (m, s)

def matrix_chain_multiply(A, s, i, j):
    if i == j:
        return A[i]
    else:
        return np.dot(matrix_chain_multiply(A, s, i, s[i, j]),
                      matrix_chain_multiply(A, s, s[i, j] + 1, j))

p = [30, 35, 15, 5, 10, 20, 25]
n = len(p) - 1
A = [None] * n
for i in range(n):
    A[i] = np.random.randint(3, size=(p[i], p[i+1]))
    print("A[%d] = " % (i))
    print(A[i])
(m, s) = matrix_chain_order(p)
print("m = ")
print(m)
print("s = ")
print(s)
B = matrix_chain_multiply(A, s, 0, n-1)
print("A[1...n] = ")
print(B)
C = A[0]
for i in range(1, n):
    C = np.dot(C, A[i])
print("Correct?", np.array_equal(B, C))
