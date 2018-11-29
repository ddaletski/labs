import numpy as np
from matplotlib import pyplot as plt


def richardson_step(x, A, b, lr):
    x_next = x + lr * (b - A @ x)
    return x_next


def richardson_generator(A, b, eps, lr):
    n = A.shape[0]

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

    print("x =", x)

    eigenvals, _ = np.linalg.eigh(A)
    min_eig = eigenvals[0]
    max_eig = eigenvals[-1]
    max_tau = 2.0 / (0.2 * min_eig + max_eig)
    min_tau = max_tau / 10
    opt_tau = 2.0 / (min_eig + max_eig)

    steps_counts = []
    taus = np.linspace(min_tau, max_tau, 100)
    for tau in taus:
        xs_ = np.array(list(richardson_generator(A, b, 1e-6, tau)))
        x_ = xs_[-1]
        steps = len(xs_)
        steps_counts.append(steps)

    fig, ax = plt.subplots(1, 1)
    ax.plot(taus, steps_counts)
    plt.title("dependence of steps count from τ")
    plt.xlabel("τ")
    plt.ylabel('steps')
    plt.savefig("out.png")

    print("x' =", x_)
    print("|x - x'| = ", max(abs(x - x_)))

    plt.show()

