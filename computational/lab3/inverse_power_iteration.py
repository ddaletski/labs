import numpy as np

def min_max_eig_std(A: np.matrix):
    eigvals = np.linalg.eigvals(A)
    return min(eigvals, key=np.abs), max(eigvals, key=np.abs)


def power_iteration(A: np.matrix):
    n = A.shape[0]
    b = np.zeros(n)
    b[0] = 1
    
    diff = b
    while np.linalg.norm(diff, ord=np.inf) > 1e-12:
        prev = b
        b = (A @ b) / np.linalg.norm(b, ord=np.inf)
        diff = np.abs(prev - b)
        yield b


def min_eig(A: np.matrix):
    A_inv = np.linalg.inv(A)
    bs = list(power_iteration(A_inv))
    b = bs[-1]
    eigenval = b.T @ A @ b / (b.T @ b)

    return len(bs), eigenval

def max_eig(A: np.matrix):
    bs = list(power_iteration(A))
    b = bs[-1]
    eigenval = b.T @ A @ b / (b.T @ b)

    return len(bs), eigenval

if __name__ == "__main__":
    np.set_printoptions(floatmode="fixed", precision=16)
    A = np.array([
        [8, 0, -4, 0, -2],
        [0, 7, 0, -4, 0],
        [-4, 0, 6, 0, -1],
        [0, -4, 0, 5, 0],
        [-2, 0, -1, 0, 4]
        ], dtype=float)


    std_min_eig, std_max_eig = min_max_eig_std(A)
    min_steps, _min_eig = min_eig(A)
    max_steps, _max_eig = max_eig(A)

    print(f"min: {std_min_eig}")
    print(f"max: {std_max_eig}")
    print(f"found min: {_min_eig} in {min_steps} steps")
    print(f"found max: {_max_eig} in {max_steps} steps")