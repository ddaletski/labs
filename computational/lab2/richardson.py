import numpy as np
from matplotlib import pyplot as plt


def richardson_step(x, A, b, lr):
    x_next = x + lr * (b - A @ x)
    return x_next


def richardson_generator(A, b, eps=1e-6, lr='optimal'):
    n = A.shape[0]

    if lr == 'optimal':
        eigenvals, _ = np.linalg.eigh(A)
        min_eig, max_eig = (eigenvals[0], eigenvals[-1])
        lr = 2 / (min_eig + max_eig)

    x_current = np.random.normal(size=n)

    while True:
        x_next = richardson_step(x_current, A, b, lr)
        yield x_next
        if np.max(np.abs(x_current - x_next)) < eps:
            raise StopIteration
        x_current = x_next



def continuous_norm(mat):
    row_sums = np.sum(np.abs(mat), 1)
    return np.max(row_sums)


if __name__ == "__main__":
    np.set_printoptions(floatmode="fixed", precision=16)
    A = np.array([
        [8, 0, -4, 0, -2],
        [0, 7, 0, -4, 0],
        [-4, 0, 6, 0, -1],
        [0, -4, 0, 5, 0],
        [-2, 0, -1, 0, 4]
        ], dtype=float)

    x = np.round(np.random.rand(5) * 21 - 10, 2) 
    b = A @ x

    print(A)
    print("b =", b)

    xs_ = np.array(list(richardson_generator(A, b, 1e-6)))
    steps = len(xs_)

    x_ = xs_[-1]

    print("x =", x)
    print("x' =", x_)
    print("steps = ", steps)
    print("|x - x'| = ", max(abs(x - x_)))

    plt.plot(np.max(np.abs(xs_ - x), axis=1))
    plt.title("convergence of x' to x")
    plt.xlabel('step')
    plt.ylabel("|x - x'|")
    plt.show()