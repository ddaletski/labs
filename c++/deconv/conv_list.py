import numpy as np

def rotate(mat):
    return np.rot90(mat, 2)

def deconv(mat):
    top, bot = np.vsplit(mat, 2)
    return np.hstack((top, rotate(bot)))

N = 16

x = np.arange(1, N+1)
print(x)

y = x.reshape((-1, 1))

while y.shape[0] > 1:
    y = deconv(y)

print(y.reshape((-1,)))
