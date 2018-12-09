import numpy as np

def min_eig_std(A: np.matrix):
    return min(np.linalg.eigvals(A), key=np.abs)

def min_eig(A: np.matrix):
    n = A.shape[0]
    b = np.zeros(n)
    b[0] = 1
    A_inv = np.linalg.inv(A)

    steps = 0
    diff = b
    while np.linalg.norm(diff, ord=np.inf) > 1e-12:
        prev = b
        b = (A_inv @ b) / np.linalg.norm(b, ord=np.inf)
        diff = np.abs(prev - b)
        steps += 1

    eigenval = b.T @ A @ b / (b.T @ b)
    return steps, eigenval


if __name__ == "__main__":
    np.set_printoptions(floatmode="fixed", precision=16)
    A = np.array([
        [8, 0, -4, 0, -2],
        [0, 7, 0, -4, 0],
        [-4, 0, 6, 0, -1],
        [0, -4, 0, 5, 0],
        [-2, 0, -1, 0, 4]
        ], dtype=float)


    std_eig = min_eig_std(A)
    steps, calculated_val = min_eig(A)

    print(f"std: {std_eig}")
    print(f"found: {calculated_val} in {steps} steps")