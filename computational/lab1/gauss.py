import numpy as np


def find_pivot(A, start_idx=0):
    argmax = (start_idx, start_idx)
    for row_idx in range(start_idx, A.shape[0]):
        for col_idx in range(start_idx, A.shape[1]):
            if np.abs(A[row_idx, col_idx]) > np.abs(A[argmax]):
                argmax = (row_idx, col_idx)

    return argmax


def solve(A: np.matrix, b: np.array):
    """ solves Ax = b """

    assert A.shape[0] == A.shape[1] == b.shape[0]

    n = A.shape[0]
    perm = np.arange(n)

    for idx in range(n - 1):
        pivot_row, pivot_col = find_pivot(A, idx)

        A[idx], A[pivot_row] = A[pivot_row].copy(), A[idx].copy()
        b[idx], b[pivot_row] = b[pivot_row].copy(), b[idx].copy()

        A[:, idx], A[:, pivot_col] = A[:, pivot_col].copy(), A[:, idx].copy()
        perm[idx], perm[pivot_col] = perm[pivot_col].copy(), perm[idx].copy()

        assert(A[idx, idx] != 0)

        for eliminated_row in range(idx+1, n):
            multiplier = A[eliminated_row, idx] / A[idx, idx]
            A[eliminated_row, :] -= (A[idx, :] * multiplier)

        print(A)
        print()

    unknowns = [None for i in range(n)]

    for idx in range(n-1, -1, -1):
        print(A[idx])
        unknowns[idx] = 0


    return unknowns


A = np.round(np.random.rand(4, 4) * 200 - 100, 2)
b = np.round(np.random.rand(4) * 20 - 10, 2)

print(A)
print(b)

solve(A, b)