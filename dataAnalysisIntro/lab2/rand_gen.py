import numpy as np
from matplotlib import pyplot as plt
import seaborn


def congruent_generator(initial, multiplier, increment, module):
    x = initial
    while(True):
        yield(x)
        x = (multiplier * x + increment) % module



params = ((2, 4, 7, 7), (6 ,17, 125, 125), (1664525, 1013904223, 2**15-1, 1000), (48271, 0, 2**31-1, 10000), (253801, 14519, 2**32-1, 10000))

fig, axes = plt.subplots(len(params), 4, figsize=(20, 20))

for i, (mult, incr, mod, count) in enumerate(params):
    for j, initial in enumerate((mod // 4 + 1, mod // 2 + 1, 3 * mod // 4 + 1, mod - 1)):
        gen = congruent_generator(initial, mult, incr, mod)
        x = [val for i, val in zip(range(count), gen)]
        axes[i, j].hist(x, bins=16)

        etalon_mean = (mod-1) / 2
        mean = np.mean(x)
        etalon_stdev = (mod-1) / np.sqrt(12)
        stdev = np.std(x)
        axes[i, j].set_title("m:{:.3f}, sd:{:.3f}".format(mean - etalon_mean, stdev - etalon_stdev))

plt.show()