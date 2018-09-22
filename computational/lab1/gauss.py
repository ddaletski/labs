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

    mat = A.copy()
    out = b.copy()

    assert mat.shape[0] == mat.shape[1] == out.shape[0]

    n = mat.shape[0]
    perm = np.arange(n)

    for idx in range(n - 1):
        pivot_row, pivot_col = find_pivot(mat, idx)

        mat[idx], mat[pivot_row] = mat[pivot_row].copy(), mat[idx].copy()
        out[idx], out[pivot_row] = out[pivot_row].copy(), out[idx].copy()

        mat[:, idx], mat[:, pivot_col] = mat[:, pivot_col].copy(), mat[:, idx].copy()
        perm[idx], perm[pivot_col] = perm[pivot_col].copy(), perm[idx].copy()

        assert(mat[idx, idx] != 0)

        for eliminated_row in range(idx+1, n):
            multiplier = mat[eliminated_row, idx] / mat[idx, idx]
            mat[eliminated_row, :] -= (mat[idx, :] * multiplier)
            out[eliminated_row] -= out[idx] * multiplier


    # calculate unknowns
    unknowns = [None for i in range(n)]
    for idx in range(n-1, -1, -1):
        x = out[idx]
        for known_idx in range(idx+1, n):
            x -= mat[idx, known_idx] * unknowns[known_idx]

        x /= mat[idx, idx]
        unknowns[idx] = x

    # apply permutation
    results = unknowns.copy()
    for i, j in enumerate(perm):
        results[j] = unknowns[i] 
 

    return results


def invert(A: np.matrix):
    mat = A.copy()

    assert mat.shape[0] == mat.shape[1]

    n = mat.shape[0]

    inv = np.identity(n)

    for idx in range(n - 1):
        pivot_row = np.argmax(mat[idx:, idx]) + idx

        mat[idx], mat[pivot_row] = mat[pivot_row].copy(), mat[idx].copy()
        inv[idx], inv[pivot_row] = inv[pivot_row].copy(), inv[idx].copy()

        assert(mat[idx, idx] != 0)

        for eliminated_row in range(idx+1, n):
            multiplier = mat[eliminated_row, idx] / mat[idx, idx]
            mat[eliminated_row, :] -= (mat[idx, :] * multiplier)
            inv[eliminated_row, :] -= (inv[idx, :] * multiplier)


    for idx in range(n-1, 0, -1):
        assert(mat[idx, idx] != 0)

        for eliminated_row in range(0, idx):
            multiplier = mat[eliminated_row, idx] / mat[idx, idx]
            mat[eliminated_row, :] -= (mat[idx, :] * multiplier)
            inv[eliminated_row, :] -= (inv[idx, :] * multiplier)


    for idx in range(n):
        inv[idx] /= mat[idx, idx]


    return inv


n = 4
A = np.round(np.random.rand(n, n) * 201 - 100, 2)
x = np.round(np.random.rand(n) * 21 - 10, 2)
b = A @ x

print(A)
print()
print(b)

x_ = solve(A, b)

print(x_ - x)

print("\n\n")

A_inv = invert(A)

print(A)
print(A_inv)

E = A @ A_inv
print(E)