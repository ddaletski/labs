import numpy as np

def rotate_around_x(tensor):
    return np.rot90(tensor, 2, (2, 0))

def rotate_around_y(tensor):
    return np.rot90(tensor, 2, (2, 1))

def deconv(tensor):
    top, bot = np.split(tensor, 2, 2)
    tensor2 = np.vstack((top, rotate_around_x(bot)))

    top, bot = np.split(tensor2, 2, 2)
    tensor3 = np.hstack((top, rotate_around_y(bot)))

    return tensor3

x = np.arange(1, 17)
x = x.reshape((1, 1, -1))
print(x, x.shape)

y = x
while y.shape[2] > 1:
    y = deconv(y)

y = y.reshape((4, 4))
print(y, y.shape)
